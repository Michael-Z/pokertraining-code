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

#ifndef BEROPOSTRIVER_H
#define BEROPOSTRIVER_H

#include <iostream>
#include "BettingRound.h"

class HandInterface;


class BettingRoundPostRiver : public BettingRound
{
public:
	BettingRoundPostRiver(HandInterface*, int, int);
	~BettingRoundPostRiver();

	void setHighestCardsValue(int theValue);
	int getHighestCardsValue() const ;
	void run();
	void postRiverRun();

private:

	int highestCardsValue;

};

#endif
