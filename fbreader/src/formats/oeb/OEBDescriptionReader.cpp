/*
 * FBReader -- electronic book reader
 * Copyright (C) 2004-2007 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <ZLUnicodeUtil.h>

#include "OEBDescriptionReader.h"

OEBDescriptionReader::OEBDescriptionReader(BookDescription &description) : myDescription(description) {
	myDescription.clearAuthor();
	myDescription.title().erase();
}

// TODO: replace "dc" by real DC scheme name
static const std::string METADATA = "dc-metadata";
static const std::string TITLE = "dc:title";
static const std::string AUTHOR_TAG = "dc:creator";
static const std::string AUTHOR_ROLE = "aut";

void OEBDescriptionReader::characterDataHandler(const char *text, int len) {
	switch (myReadState) {
		case READ_NONE:
			break;
		case READ_AUTHOR:
			myCurrentAuthor.append(text, len);
			break;
		case READ_TITLE:
			myDescription.title().append(text, len);
			break;
	}
}

void OEBDescriptionReader::startElementHandler(const char *tag, const char **attributes) {
	const std::string tagString = ZLUnicodeUtil::toLower(tag);
	if (METADATA == tagString) {
		myReadMetaData = true;
	} else if (myReadMetaData) {
		if (TITLE == tagString) {
			myReadState = READ_TITLE;
		} else if (AUTHOR_TAG == tagString) {
			const char *role = attributeValue(attributes, "role");
			if ((role != 0) && (AUTHOR_ROLE == role)) {
				myReadState = READ_AUTHOR;
			}
		}
	}
}

void OEBDescriptionReader::endElementHandler(const char *tag) {
	const std::string tagString = ZLUnicodeUtil::toLower(tag);
	if (METADATA == tagString) {
		interrupt();
	} else {
		if (!myCurrentAuthor.empty()) {
			myDescription.addAuthor(myCurrentAuthor);
			myCurrentAuthor.erase();
		}
		myReadState = READ_NONE;
	}
}

bool OEBDescriptionReader::readDescription(const std::string &fileName) {
	myReadMetaData = false;
	myReadState = READ_NONE;
	return readDocument(fileName);
}
