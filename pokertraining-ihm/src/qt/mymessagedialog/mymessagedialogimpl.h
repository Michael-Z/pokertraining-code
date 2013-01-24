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
#ifndef MYMESSAGEDIALOGIMPL_H
#define MYMESSAGEDIALOGIMPL_H

#ifdef GUI_800x480
#include "ui_mymessagedialog_800x480.h"
#else
#include "ui_mymessagedialog.h"
#endif

class ConfigFile;

class myMessageDialogImpl: public QDialog, public Ui::myMessageDialog
{
	Q_OBJECT
public:

	myMessageDialogImpl(ConfigFile *, QWidget *parent = 0);

public slots:

	bool checkIfMesssageWillBeDisplayed(int id);
	int exec(int messageId, QString msg, QString title, QPixmap pix, QDialogButtonBox::StandardButtons buttons, bool showCheckBox = false);
	void show(int messageId, QString msg, QString title, QPixmap pix, QDialogButtonBox::StandardButtons buttons, bool showCheckBox = false);
	void accept();
	void reject();
	void writeConfig();

private:

	ConfigFile *myConfig;
	int currentMsgId;
	std::list<std::string> currentMsgShowList;

};

#endif

// messages --> id: content
//1: leave lobby during online game: Question(Do you really wanna leave?)
//2: join invite only game: Info(You can invite people with right click ...)
//3: reciev invite to game: Question(You've been invited to the game <b>%1</b> by <b>%2</b>.<br>Do you want to join this game?)
//4: click ignore player: Question(Do you really want to put this player on ignore List?)
//5: add a broken (fields missing) game table style: Info(Selected game table style \"%1\" seems to be incomplete or defective. \n\nThe value(s) of \"%2\" is/are missing. \n\nPlease contact the game table style builder %3.)
//6: close gametable: Do you really wanna quit?
