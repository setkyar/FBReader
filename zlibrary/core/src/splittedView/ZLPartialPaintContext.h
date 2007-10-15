/*
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

#ifndef __ZLPARTIALPAINTCONTEXT_H__
#define __ZLPARTIALPAINTCONTEXT_H__

#include <ZLPaintContext.h>

class ZLPartialPaintContext : public ZLPaintContext {

public:
	ZLPartialPaintContext(ZLPaintContext &base, bool left);

	void clear(ZLColor color);

	void setFont(const std::string &family, int size, bool bold, bool italic);
	void setColor(ZLColor color, LineStyle style);
	void setFillColor(ZLColor color, FillStyle style);

	int width() const;
	int height() const;
	
	int stringWidth(const char *str, int len) const;
	int spaceWidth() const;
	int stringHeight() const;
	int descent() const;
	void drawString(int x, int y, const char *str, int len);

	void drawImage(int x, int y, const ZLImageData &image);

	void drawLine(int x0, int y0, int x1, int y1);
	void fillRectangle(int x0, int y0, int x1, int y1);
	void drawFilledCircle(int x, int y, int r);

	const std::string realFontFamilyName(std::string &fontFamily) const;

	int xBaseToPartial(int x) const;
	int xPartialToBase(int x) const;

protected:
	void fillFamiliesList(std::vector<std::string> &families) const;

private:
	ZLPaintContext &myBaseContext;
	bool myIsLeft;
};

#endif /* __ZLPARTIALPAINTCONTEXT_H__ */
