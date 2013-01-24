/*****************************************************************************
 * PokerTraining - THNL training software, based on the PokerTH GUI          *
 * Copyright (C) 2013 Marc Ennaji                                            *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as            *
 * published by the Free Software Foundation, either version 3 of the        *
 * License, or (at your option) any later version.                           *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *****************************************************************************/
#include "changecompleteblindsdialogimpl.h"
#include <qt/mymessagebox/mymessagebox.h>
#include <iostream>


changeCompleteBlindsDialogImpl::changeCompleteBlindsDialogImpl(QWidget *parent, ConfigFile *c)
	: QDialog(parent), myConfig(c), settingsCorrect(TRUE)
{
#ifdef __APPLE__
	setWindowModality(Qt::ApplicationModal);
	setWindowFlags(Qt::WindowSystemMenuHint | Qt::CustomizeWindowHint | Qt::Dialog);
#endif
	setupUi(this);

	connect( pushButton_add, SIGNAL( clicked() ), this, SLOT( addBlindValueToList() ) );
	connect( pushButton_delete, SIGNAL( clicked() ), this, SLOT( removeBlindFromList() ) );
	connect( spinBox_firstSmallBlind, SIGNAL( valueChanged(int) ), this, SLOT( updateSpinBoxInputMinimum(int) ) );

}

void changeCompleteBlindsDialogImpl::exec()
{


	QDialog::exec();
}

void changeCompleteBlindsDialogImpl::updateSpinBoxInputMinimum(int value)
{
	spinBox_input->setMinimum(value+1);
}

void changeCompleteBlindsDialogImpl::addBlindValueToList()
{

	if(listWidget_blinds->count() == 30) {
		MyMessageBox::warning(this, tr("Manual Blinds Order"),
							 tr("You cannot set more than 30 manual blinds."),
							 QMessageBox::Close);
	} else {
		listWidget_blinds->addItem(QString::number(spinBox_input->value(),10));
		sortBlindsList();
	}
}

void changeCompleteBlindsDialogImpl::removeBlindFromList()
{

	listWidget_blinds->takeItem(listWidget_blinds->currentRow());
	sortBlindsList();
}

void changeCompleteBlindsDialogImpl::sortBlindsList()
{

	int i;
	QList<int> tempIntList;
	QStringList tempStringList;
	bool ok = TRUE;

	for(i=0; i<listWidget_blinds->count(); i++) {
// 		std::cout << listWidget_blinds->item(i)->text().toInt(&ok,10) << "\n";
		tempIntList << listWidget_blinds->item(i)->text().toInt(&ok,10);
	}

	qStableSort(tempIntList.begin(), tempIntList.end());
//
	for(i=0; i<tempIntList.count(); i++) {
//
// 		std::cout << tempIntList[i] << "\n";
		tempStringList << QString::number(tempIntList[i],10);
	}
//
	listWidget_blinds->clear();
	listWidget_blinds->addItems(tempStringList);
}
