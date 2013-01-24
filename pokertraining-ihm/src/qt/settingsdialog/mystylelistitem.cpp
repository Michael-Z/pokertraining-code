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
#include <qt/settingsdialog/mystylelistitem.h>

MyStyleListItem::MyStyleListItem(QStringList s, QTreeWidget *w)
	: QTreeWidgetItem(w, s, QTreeWidgetItem::UserType)
{
}

MyStyleListItem::~MyStyleListItem()
{
}

bool MyStyleListItem::operator<( const QTreeWidgetItem &other ) const
{
	return text(0).toLower() < other.text(0).toLower();
}

