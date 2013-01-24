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

#include "BettingRoundpostriver.h"
#include <engine/handinterface.h>
#include <game_defs.h>
#include "Player.h"

#include <iostream>

using namespace std;

BettingRoundPostRiver::BettingRoundPostRiver(HandInterface* hi, int dP, int sB) : BettingRound(hi, dP, sB, GAME_STATE_POST_RIVER), highestCardsValue(0)
{
}

BettingRoundPostRiver::~BettingRoundPostRiver()
{
}

void BettingRoundPostRiver::run()
{
}

void BettingRoundPostRiver::postRiverRun()
{

	PlayerListConstIterator it_c;
	PlayerListIterator it;

	// who is the winner
	for(it_c=getHand()->getActivePlayerList()->begin(); it_c!=getHand()->getActivePlayerList()->end(); ++it_c) {

		if( (*it_c)->getAction() != PLAYER_ACTION_FOLD && (*it_c)->getCardsValueInt() > highestCardsValue ) {
			highestCardsValue = (*it_c)->getCardsValueInt();
		}
	}

	int potPlayers = 0;

	for(it_c=getHand()->getActivePlayerList()->begin(); it_c!=getHand()->getActivePlayerList()->end(); ++it_c) {
		if( (*it_c)->getAction() != PLAYER_ACTION_FOLD) {
			potPlayers++;
		}
	}

	getHand()->getBoard()->determinePlayerNeedToShowCards();

	// Pot-Verteilung
	getHand()->getBoard()->distributePot();

	//Pot auf 0 setzen
	getHand()->getBoard()->setPot(0);

	// logging
	int nonfoldPlayersCounter = 0;
	for (it_c=getHand()->getActivePlayerList()->begin(); it_c!=getHand()->getActivePlayerList()->end(); ++it_c) {
		if ((*it_c)->getAction() != PLAYER_ACTION_FOLD) nonfoldPlayersCounter++;
	}
	if(nonfoldPlayersCounter>1) {
		if(getHand()->getLog()) getHand()->getLog()->logHoleCardsHandName(getHand()->getActivePlayerList());
	}
	if(getHand()->getLog()) {
		getHand()->getLog()->logHandWinner(getHand()->getActivePlayerList(), highestCardsValue, getHand()->getBoard()->getWinners());
//		getHand()->getLog()->logPlayerSitsOut(getHand()->getActivePlayerList());
		getHand()->getLog()->logGameWinner(getHand()->getActivePlayerList());
		getHand()->getLog()->logAfterHand();
		getHand()->getLog()->logPlayersStatistics(getHand()->getActivePlayerList());
	}

	//starte die Animaionsreihe
	getHand()->getGuiInterface()->postRiverRunAnimation1();
}
void BettingRoundPostRiver::setHighestCardsValue(int theValue) {
	highestCardsValue = theValue;
}
int BettingRoundPostRiver::getHighestCardsValue() const {
	return highestCardsValue;
}