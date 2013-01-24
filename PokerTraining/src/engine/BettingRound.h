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

#ifndef BERO_H
#define BERO_H


#include "game_defs.h"

#include <engine/BettingRoundinterface.h>
#include <engine/handinterface.h>

class BettingRound : public BettingRoundInterface
{
public:
	BettingRound(HandInterface* hi, unsigned dP, int sB, GameState gS);
	~BettingRound();

	GameState getBettingRoundID() const ;
	int getHighestCardsValue() const;
	void setHighestCardsValue(int /*theValue*/);
	void setMinimumRaise ( int theValue ) ;
	int getMinimumRaise() const;
	void setFullBetRule ( bool theValue );
	bool getFullBetRule() const;
	void skipFirstRunGui();
	void nextPlayer();
	void run();
	void postRiverRun();

protected:

	HandInterface* getHand() const;

	int getDealerPosition() const;
	void setDealerPosition(int theValue);

	void setCurrentPlayersTurnId(unsigned theValue);
	unsigned getCurrentPlayersTurnId() const;

	void setFirstRoundLastPlayersTurnId(unsigned theValue);
	unsigned getFirstRoundLastPlayersTurnId() const ;

	void setCurrentPlayersTurnIt(PlayerListIterator theValue);
	PlayerListIterator getCurrentPlayersTurnIt() const;

	void setLastPlayersTurnIt(PlayerListIterator theValue);
	PlayerListIterator getLastPlayersTurnIt() const;

	void setHighestSet(int theValue);
	int getHighestSet() const;

	void setFirstRun(bool theValue) ;
	bool getFirstRun() const ;

	void setFirstRound(bool theValue) ;
	bool getFirstRound() const ;


	void setDealerPositionId(unsigned theValue);
	unsigned getDealerPositionId() const;

	void setSmallBlindPositionId(unsigned theValue) ;
	unsigned getSmallBlindPositionId() const ;

	void setBigBlindPositionId(unsigned theValue);
	unsigned getBigBlindPositionId() const ;

	void setSmallBlindPosition(int theValue);
	int getSmallBlindPosition() const ;

	void setSmallBlind(int theValue);
	int getSmallBlind() const ;

private:

	HandInterface* myHand;

	const GameState myBettingRoundID;
	int dealerPosition;
	int smallBlindPosition;

	unsigned dealerPositionId;
	unsigned smallBlindPositionId;
	unsigned bigBlindPositionId;


	int smallBlind;
	int highestSet;
	int minimumRaise;
	bool fullBetRule;

	bool firstRun;
	bool firstRunGui; // HACK
	bool firstRound;
	bool firstHeadsUpRound;

	PlayerListIterator currentPlayersTurnIt; // iterator for runningPlayerList
	PlayerListIterator lastPlayersTurnIt; // iterator for runningPlayerList

	unsigned currentPlayersTurnId;
	unsigned firstRoundLastPlayersTurnId;

	bool logBoardCardsDone;


};

#endif
