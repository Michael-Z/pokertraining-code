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
#ifndef STDSESSION_H
#define STDSESSION_H

#include <boost/shared_ptr.hpp>
#include <string>

#include "gamedata.h"
#include "game_defs.h"


class GuiInterface;
class Game;
class ConfigFile;
class Log;
class QtToolsInterface;

class Session
{
public:

	Session(GuiInterface*, ConfigFile*, Log*);

	~Session();

	// Only one of the two inits should be called.
	bool init();
//	void init(boost::shared_ptr<AvatarManager> manager);

	void addOwnAvatar(const std::string &avatarFile);

	void startGame(const GameData &gameData, const StartData &startData);

	boost::shared_ptr<Game> getCurrentGame();

	GuiInterface *getGui();

	Log* getLog() {
		return myLog;
	}


	GameInfo getClientGameInfo(unsigned gameId) const;
	unsigned getGameIdOfPlayer(unsigned playerId) const;
	unsigned getClientCurrentGameId() const;
	unsigned getClientUniquePlayerId() const;

private:

	int currentGameNum;

	std::string myIrcNick;

	boost::shared_ptr<Game> currentGame;
	GuiInterface *myGui;
	ConfigFile *myConfig;
	Log *myLog;
	QtToolsInterface *myQtToolsInterface;
};

#endif
