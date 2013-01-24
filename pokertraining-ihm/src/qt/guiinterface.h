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
#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

//#include <net/clientcallback.h>
//#include <net/servercallback.h>
//#include <net/irccallback.h>
#include <game_defs.h>
#include <string>
#include <boost/shared_ptr.hpp>

class guiLog;
class Session;
class gameTableImpl;

// class GuiInterface : public ClientCallback, public ServerCallback, public IrcCallback

class GuiInterface
{
public:
	virtual ~GuiInterface();

	virtual void initGui(int speed) =0;

	virtual boost::shared_ptr<Session> getSession() =0;
	virtual void setSession(boost::shared_ptr<Session> session) =0;

	virtual gameTableImpl *getW() const=0;
	virtual guiLog* getGuiLog() const=0;


	//refresh-Funktionen
	virtual void refreshSet() const=0;
	virtual void refreshCash() const=0;
	virtual void refreshAction(int =-1, int =-1) const=0;
	virtual void refreshChangePlayer() const=0;
	virtual void refreshPot() const=0;
	virtual void refreshGroupbox(int =-1, int =-1) const=0;
	virtual void refreshAll() const=0;
	virtual void refreshPlayerName() const=0;
	virtual void refreshButton() const =0;
	virtual void refreshGameLabels(GameState state) const=0;

	virtual void setPlayerAvatar(int myUniqueID, const std::string &myAvatar) const=0;
	virtual void waitForGuiUpdateDone() const=0;

	// Karten-Funktionen
	virtual void dealBettingRoundCards(int) =0;
	virtual void dealHoleCards()=0;
	virtual void dealFlopCards()=0;
	virtual void dealTurnCard()=0;
	virtual void dealRiverCard()=0;

	virtual void nextPlayerAnimation()=0;

	virtual void beRoAnimation2(int)=0;

	virtual void preflopAnimation1()=0;
	virtual void preflopAnimation2()=0;

	virtual void flopAnimation1()=0;
	virtual void flopAnimation2()=0;

	virtual void turnAnimation1()=0;
	virtual void turnAnimation2()=0;

	virtual void riverAnimation1()=0;
	virtual void riverAnimation2()=0;

	virtual void postRiverAnimation1()=0;
	virtual void postRiverRunAnimation1()=0;
	virtual void flipHolecardsAllIn()=0;

	virtual void nextRoundCleanGui()=0;
	virtual void meInAction()=0;
	virtual void showCards(unsigned playerId)=0;
	virtual void updateMyButtonsState()=0;
	virtual void disableMyButtons()=0;

	//log.cpp
	virtual void logPlayerActionMsg(std::string playName, int action, int setValue) =0;
	virtual void logNewGameHandMsg(int gameID, int HandID) =0;
	virtual	void logPlayerWinsMsg(std::string playerName, int pot, bool main) = 0;
//	virtual	void logPlayerSitsOut(std::string playerName) = 0;
	virtual void logNewBlindsSetsMsg(int sbSet, int bbSet, std::string sbName, std::string bbName) =0;
	virtual void logDealBoardCardsMsg(int roundID, int card1, int card2, int card3, int card4 = -1, int card5 = -1) = 0;
	virtual void logFlipHoleCardsMsg(std::string playerName, int card1, int card2, int cardsValueInt = -1, std::string showHas = "shows") = 0;
	virtual void logPlayerWinGame(std::string playerName, int gameID) =0;
	virtual void flushLogAtGame(int gameID) =0;
	virtual void flushLogAtHand() =0;


};

#endif
