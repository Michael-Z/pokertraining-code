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
#include <engine/HumanPlayer.h>

using namespace std;

HumanPlayer::HumanPlayer(ConfigFile *c, int id, unsigned uniqueId, PlayerType type, std::string name, 
						std::string avatar, int sC, bool aS, bool sotS, int mB):
	Player(c, id, uniqueId, type, name, avatar, sC, aS, sotS, mB){}

	
HumanPlayer::~HumanPlayer(){}



