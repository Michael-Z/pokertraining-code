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
#ifndef QTTOOLSINTERFACE_H
#define QTTOOLSINTERFACE_H

#include <string>

class QtToolsInterface
{
public:
	virtual ~QtToolsInterface();

	//qthelper.cpp
	virtual std::string stringToUtf8(const std::string &) =0;
	virtual std::string stringFromUtf8(const std::string &) =0;
	virtual std::string getDefaultLanguage() =0;
	virtual std::string getDataPathStdString(const char *argv0) =0;


};

QtToolsInterface *CreateQtToolsWrapper();

#endif
