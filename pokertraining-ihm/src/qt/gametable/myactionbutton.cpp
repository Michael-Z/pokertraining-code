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
#include "myactionbutton.h"
#include <qt/styles/gametablestylereader.h>

using namespace std;

MyActionButton::MyActionButton(QWidget* parent)
	: QPushButton(parent), myStyle(NULL), eatMyEvents(false)
{
	myStyle = NULL;
}


MyActionButton::~MyActionButton()
{
}

void MyActionButton::setFKeyText ( const QString& theValue ) {
	fKeyText = theValue;
}

void MyActionButton::setStyle ( GameTableStyleReader* theValue ) {
	assert(theValue != NULL);
	myStyle = theValue;
}

void MyActionButton::setEatMyEvents(bool e) {
	eatMyEvents = e;
}

void MyActionButton::paintEvent(QPaintEvent * event)
{
	assert(myStyle != NULL);

	QPushButton::paintEvent(event);

	QPainter painter(this);
	painter.setPen(QColor("#"+myStyle->getFKeyIndicatorColor()));
	painter.setOpacity(0.5);
	QFont f= painter.font();
	f.setPixelSize(9);
	painter.setFont(f);
	if(objectName()==("pushButton_AllIn")) {
		painter.drawText(6,6,15,15,Qt::AlignLeft,fKeyText);
	} else if(objectName()==("pushButton_showMyCards")) {
		painter.drawText(6,6,15,15,Qt::AlignLeft,QString("F5"));
	} else {
		painter.drawText(8,15,15,15,Qt::AlignLeft,fKeyText);
	}
}

bool MyActionButton::event(QEvent *event)
{
	if ((event->type() == QEvent::KeyPress || event->type() == QEvent::MouseButtonPress) && eatMyEvents ) {
		return true;
	}
	return QWidget::event(event);
}
