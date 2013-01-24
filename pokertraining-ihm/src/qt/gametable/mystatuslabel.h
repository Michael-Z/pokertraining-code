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
#ifndef MYSTATUSLABEL_H
#define MYSTATUSLABEL_H

#include <iostream>

#include <QtGui>
#include <QtCore>

class gameTableImpl;

class MyStatusLabel : public QLabel
{
	Q_OBJECT
public:
	MyStatusLabel(QGroupBox*);

	~MyStatusLabel();


	void setW ( gameTableImpl* theValue ) {
		myW = theValue;
	}

	void mousePressEvent ( QMouseEvent *);
	void mouseReleaseEvent ( QMouseEvent *);


private:

	gameTableImpl *myW;
	bool mousePress;

};

#endif
