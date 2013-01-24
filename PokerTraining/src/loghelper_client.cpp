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

#ifdef POKERTRAINING_DEDICATED_SERVER
#error This file is only for the client.
#endif

#include <loghelper.h>
#include <iostream>


using namespace std;


static int g_logLevel = 1;

void
loghelper_init(const std::string & /*logDir*/, int logLevel)
{
	// Do not log to file as client.
	g_logLevel = logLevel;
}

void
internal_log_err(const string &msg)
{
	cerr << msg;
}

void
internal_log_msg(const std::string &msg)
{
	if (g_logLevel)
		cout << msg;
}

void
internal_log_level(const std::string &msg, int logLevel)
{
	if (g_logLevel >= logLevel)
		cout << msg;
}

