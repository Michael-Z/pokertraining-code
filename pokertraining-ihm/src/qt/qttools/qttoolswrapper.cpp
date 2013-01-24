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
#include "qttoolswrapper.h"
#include "qt/qttools/qthelper/qthelper.h"

using namespace std;


QtToolsInterface *CreateQtToolsWrapper()
{
	return new QtToolsWrapper;
}

QtToolsWrapper::QtToolsWrapper() : myQtHelper(0)
{

	myQtHelper = new QtHelper();
}


QtToolsWrapper::~QtToolsWrapper()
{
	delete myQtHelper;
	myQtHelper = 0;
}

std::string QtToolsWrapper::stringToUtf8(const std::string &myString)
{
	return myQtHelper->stringToUtf8(myString);
}
std::string QtToolsWrapper::stringFromUtf8(const std::string &myString)
{
	return myQtHelper->stringFromUtf8(myString);
}
std::string QtToolsWrapper::getDefaultLanguage()
{
	return myQtHelper->getDefaultLanguage();
}
std::string QtToolsWrapper::getDataPathStdString(const char * argv0)
{
	return myQtHelper->getDataPathStdString(argv0);
}

