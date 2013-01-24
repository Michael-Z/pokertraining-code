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

#include "exception.h"
#include <sstream>

using namespace std;

Exception::Exception(const char *sourcefile, int sourceline, int errorId, int osErrorCode)
	: m_errorId(errorId), m_osErrorCode(osErrorCode)
{
	ostringstream msgStream;
	msgStream << sourcefile << " (" << sourceline << "): Error " << errorId;
	if (osErrorCode)
		msgStream << " (system error " << osErrorCode << ")";
	m_msg = msgStream.str();
}

Exception::Exception(const char *sourcefile, int sourceline, int errorId)
	: m_errorId(errorId)
{
	ostringstream msgStream;
	msgStream << sourcefile << " (" << sourceline << "): Error " << errorId;
	m_msg = msgStream.str();
}

Exception::~Exception() throw()
{
}

const char *
Exception::what() const throw()
{
	return m_msg.c_str();
}



