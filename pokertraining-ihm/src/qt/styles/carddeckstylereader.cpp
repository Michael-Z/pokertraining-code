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
#include "carddeckstylereader.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <qt/mymessagebox/mymessagebox.h>
#include "game_defs.h"

using namespace std;

CardDeckStyleReader::CardDeckStyleReader(ConfigFile *c, QWidget *w) : myConfig(c), myW(w), fallBack(0), loadedSuccessfull(0)
{

}


CardDeckStyleReader::~CardDeckStyleReader()
{
}

void CardDeckStyleReader::readStyleFile(QString file)
{
#ifdef ANDROID
//on Android we use just the defaul style packed with the binary via qrc
    currentFileName = ":/android/android-data/gfx/cards/default_800x480/defaultdeckstyle_800x480.xml";
    currentDir = ":/android/android-data/gfx/cards/default_800x480/";
#else
	//if style file failed --> default style fallback
	if(QFile(file).exists()) {
		currentFileName = file;
	} else {
		currentFileName = QString::fromUtf8(myConfig->readConfigString("AppDataDir").c_str())+"gfx/cards/default/defaultdeckstyle.xml";
		fallBack = 1;
	}

	QFileInfo info(currentFileName);
	currentDir = info.absolutePath()+"/";
#endif
        QFile myFile(currentFileName);
        myFile.open(QIODevice::ReadOnly);
        fileContent = myFile.readAll();

	//start reading the file and fill vars
	string tempString1("");

	TiXmlDocument doc;
	doc.Parse(fileContent.constData());

	if(doc.RootElement()) {
		TiXmlHandle docHandle( &doc );

		TiXmlElement *GameTableElement = docHandle.FirstChild( "PokerTraining" ).FirstChild( "TableStyle" ).ToElement();
		if(GameTableElement) {
			MyMessageBox::warning(myW, tr("Card Deck Style Error"),
								 tr("A game table style was selected instead of a card deck style.\nPlease select a card deck style and try again!"),
								 QMessageBox::Ok);
		} else {

			TiXmlElement* itemsList = docHandle.FirstChild( "PokerTraining" ).FirstChild( "CardDeck" ).FirstChild().ToElement();
			for( ; itemsList; itemsList=itemsList->NextSiblingElement()) {
				const char *tmpStr1 = itemsList->Attribute("value");
				if (tmpStr1) {
					tempString1 = tmpStr1;

					if(itemsList->ValueStr() == "StyleDescription") {
						StyleDescription = QString::fromUtf8(tempString1.c_str());
					} else if(itemsList->ValueStr() == "StyleMaintainerName") {
						StyleMaintainerName = QString::fromUtf8(tempString1.c_str());
					} else if(itemsList->ValueStr() == "StyleMaintainerEMail") {
						StyleMaintainerEMail = QString::fromUtf8(tempString1.c_str());
					} else if(itemsList->ValueStr() == "StyleCreateDate") {
						StyleCreateDate = QString::fromUtf8(tempString1.c_str());
					} else if(itemsList->ValueStr() == "PokerTrainingStyleFileVersion") {
						PokerTrainingStyleFileVersion = QString::fromUtf8(tempString1.c_str());
					} else if (itemsList->ValueStr() == "Preview") {
						Preview = currentDir+QString::fromUtf8(tempString1.c_str());
					}
				}
			}
			//check if style items are left and show warning
			leftItems.clear();

			if(StyleDescription == "") {
				leftItems << "StyleDescription";
			}
			if(StyleMaintainerName == "") {
				leftItems << "StyleMaintainerName";
			}
			if(StyleMaintainerEMail == "") {
				leftItems << "StyleMaintainerEMail";
			}
			if(StyleCreateDate == "") {
				leftItems << "StyleCreateDate";
			}
			if(PokerTrainingStyleFileVersion == "") {
				leftItems << "PokerTrainingStyleFileVersion";
			}

			//check if all files are there
			cardsLeft.clear();
			int i;
			for(i=0; i<52; i++) {
				QString cardString(QString::number(i)+".png");
				if(!QDir(currentDir).exists(cardString)) {
					cardsLeft << cardString;
				}
			}
			if(!QDir(currentDir).exists("flipside.png")) {
				cardsLeft << "flipside.png";
			}

			// set loadedSuccessfull TRUE if everything works
			if(leftItems.isEmpty() && cardsLeft.isEmpty() && PokerTrainingStyleFileVersion != "" && PokerTrainingStyleFileVersion.toInt() == POKERTRAINING_CD_STYLE_FILE_VERSION)
				loadedSuccessfull = 1;
			else
				loadedSuccessfull = 0;

			if(!leftItems.isEmpty() && myW != 0) showLeftItemsErrorMessage(StyleDescription, leftItems, StyleMaintainerEMail);
			else {
				if(!cardsLeft.isEmpty() && myW != 0) showCardsLeftErrorMessage(StyleDescription, cardsLeft, StyleMaintainerEMail);
				//check for style file version
				if(PokerTrainingStyleFileVersion != "" && PokerTrainingStyleFileVersion.toInt() != POKERTRAINING_CD_STYLE_FILE_VERSION) {
					QString EMail;
					if(StyleMaintainerEMail != "NULL") EMail = StyleMaintainerEMail;
					MyMessageBox::warning(myW, tr("Card Deck Style Error"),
										 tr("Selected card deck style \"%1\" seems to be outdated. \n The current PokerTraining card deck style version is \"%2\", but this style has version \"%3\" set. \n\nPlease contact the card deck style builder %4.").arg(StyleDescription).arg(POKERTRAINING_CD_STYLE_FILE_VERSION).arg(PokerTrainingStyleFileVersion).arg(EMail),
										 QMessageBox::Ok);
				}
			}
		}
	} else {
		loadedSuccessfull = 0;
		MyMessageBox::warning(myW, tr("Card Deck Style Error"),
							 tr("Cannot load card deck style file: %1 \n\nPlease check the style file or choose another style!").arg(currentFileName),
							 QMessageBox::Ok);
	}

}

void CardDeckStyleReader::showLeftItemsErrorMessage(QString style, QStringList failedItems, QString email)
{
	QString items = failedItems.join(", ");
	QString EMail;
	if(email != "NULL") EMail = email;

	MyMessageBox::warning(myW, tr("Card Deck Style Error"),
						 tr("Selected card deck style \"%1\" seems to be incomplete or defective. \n\nThe value(s) of \"%2\" is/are missing. \n\nPlease contact the card deck style builder %3.").arg(style).arg(items).arg(EMail),
						 QMessageBox::Ok);
}

void CardDeckStyleReader::showCardsLeftErrorMessage(QString style, QStringList failedItems, QString email)
{
	QString items = failedItems.join(", ");
	QString EMail;
	if(email != "NULL") EMail = email;

	MyMessageBox::warning(myW, tr("Card Deck Style Error"),
						 tr("Selected card deck style \"%1\" seems to be incomplete or defective. \nThe card picture(s) \"%2\" is/are not available. \n\nPlease contact the card deck style builder %3.").arg(style).arg(items).arg(EMail),
						 QMessageBox::Ok);
}
