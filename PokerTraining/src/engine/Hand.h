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

#ifndef HAND_H
#define HAND_H

#include <engine/enginefactory.h>
#include <qt/guiinterface.h>
#include <engine/boardinterface.h>
#include <engine/Player.h>
#include <engine/handinterface.h>
#include <engine/BettingRoundinterface.h>

#include <vector>

class Log;

class Hand : public HandInterface
{
public:
	Hand(boost::shared_ptr<EngineFactory> f, GuiInterface*, boost::shared_ptr<BoardInterface>, Log*, PlayerList, PlayerList, PlayerList, int, int, unsigned, int, int);
	~Hand();

	void start();

	PlayerList getSeatsList() const {
		return seatsList;
	}
	PlayerList getActivePlayerList() const {
		return activePlayerList;
	}
	PlayerList getRunningPlayerList() const {
		return runningPlayerList;
	}

	boost::shared_ptr<BoardInterface> getBoard() const {
		return myBoard;
	}
	boost::shared_ptr<BettingRoundInterface> getPreflop() const {
		return myBettingRound[GAME_STATE_PREFLOP];
	}
	boost::shared_ptr<BettingRoundInterface> getFlop() const {
		return myBettingRound[GAME_STATE_FLOP];
	}
	boost::shared_ptr<BettingRoundInterface> getTurn() const {
		return myBettingRound[GAME_STATE_TURN];
	}
	boost::shared_ptr<BettingRoundInterface> getRiver() const {
		return myBettingRound[GAME_STATE_RIVER];
	}
	GuiInterface* getGuiInterface() const {
		return myGui;
	}
	boost::shared_ptr<BettingRoundInterface> getCurrentBettingRound() const {
		return myBettingRound[currentRound];
	}

	Log* getLog() const {
		return myLog;
	}

	void setID(int theValue) {
		myID = theValue;
	}
	int getID() const {
		return myID;
	}

	void setStartQuantityPlayers(int theValue) {
		startQuantityPlayers = theValue;
	}
	int getStartQuantityPlayers() const {
		return startQuantityPlayers;
	}

	void setCurrentRound(GameState theValue) {
		currentRound = theValue;
		if(myLog) myLog->setCurrentRound(currentRound);
	}
	GameState getCurrentRound() const {
		return currentRound;
	}
	GameState getRoundBeforePostRiver() const {
		return roundBeforePostRiver;
	}

	void setDealerPosition(int theValue) {
		dealerPosition = theValue;
	}
	int getDealerPosition() const {
		return dealerPosition;
	}

	void setSmallBlind(int theValue) {
		smallBlind = theValue;
	}
	int getSmallBlind() const {
		return smallBlind;
	}

	void setAllInCondition(bool theValue) {
		allInCondition = theValue;
	}
	bool getAllInCondition() const {
		return allInCondition;
	}

	void setStartCash(int theValue)	{
		startCash = theValue;
	}
	int getStartCash() const {
		return startCash;
	}

	void setPreviousPlayerID(int theValue) {
		previousPlayerID = theValue;
	}
	int getPreviousPlayerID() const {
		return previousPlayerID;
	}

	void setLastActionPlayerID ( unsigned theValue );

	unsigned getLastActionPlayerID() const {
		return lastActionPlayerID;
	}

	void setCardsShown(bool theValue) {
		cardsShown = theValue;
	}
	bool getCardsShown() const {
		return cardsShown;
	}

	void assignButtons();
	void setBlinds();

	void switchRounds();

	int getPreflopCallsNumber();
	int getPreflopRaisesNumber();
	int getFlopBetsOrRaisesNumber();
	int getTurnBetsOrRaisesNumber();
	int getRiverBetsOrRaisesNumber();

	std::vector<PlayerPosition> getRaisersPositions();
	std::vector<PlayerPosition> getCallersPositions();
	int getLastRaiserID();
	int getPreflopLastRaiserID();
	void setPreflopLastRaiserID(int id);

protected:

	PlayerListIterator getSeatIt(unsigned) const;
	PlayerListIterator getActivePlayerIt(unsigned) const;
	PlayerListIterator getRunningPlayerIt(unsigned) const;

private:

	boost::shared_ptr<EngineFactory> myFactory;
	GuiInterface *myGui;
	boost::shared_ptr<BoardInterface> myBoard;
	Log *myLog;

	PlayerList seatsList; // all player
	PlayerList activePlayerList; // all player who are not out
	PlayerList runningPlayerList; // all player who are not folded, not all in and not out

	std::vector<boost::shared_ptr<BettingRoundInterface> > myBettingRound;

	int myID;
	int startQuantityPlayers;
	unsigned dealerPosition;
	unsigned smallBlindPosition;
	unsigned bigBlindPosition;
	GameState currentRound;
	GameState roundBeforePostRiver;
	int smallBlind;
	int startCash;

	int previousPlayerID;
	int preflopLastRaiserID;
	unsigned lastActionPlayerID;

	bool allInCondition;
	bool cardsShown;
};

#endif


