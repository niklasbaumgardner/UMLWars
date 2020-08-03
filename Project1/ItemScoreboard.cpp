/**
* \file ItemScoreboard.cpp
*
* \author Niklas Baumgardner
*/

#include "pch.h"
#include "ItemScoreboard.h"
#include "Game.h"
#include <sstream>

using namespace Gdiplus;
using namespace std;

/**
 * Scoreboard class
 * \param game game
 */
CItemScoreboard::CItemScoreboard(CGame* game) : CItem(game)
{

}

/**
 * Draw this item
 * \param graphics Graphics device to draw on
 */
void CItemScoreboard::Draw(Gdiplus::Graphics* graphics) 
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 20, 1);
	Gdiplus::Font numfont(&fontFamily, 30, 1);

	double height = CGame::Height;
	double width = CGame::Width;

	// Draws correct
	wstringstream str;
	str << mCorrect;
	SolidBrush cyan(Color(17, 214, 198));
	graphics->DrawString(L"Correct", -1, &font, PointF(-width/3, height/10), &cyan);
	graphics->DrawString(str.str().c_str(), -1, &numfont, PointF(-width / 3, height / 20), &cyan);

	// Draws Missed
	wstringstream str2;
	str2 << mMissed;
	graphics->DrawString(L"Missed", -1, &font, PointF(0, height / 10), &cyan);
	graphics->DrawString(str2.str().c_str(), -1, &numfont, PointF(0, height / 20), &cyan);

	// Draws unfair score
	wstringstream str3;
	str3 << mUnfair;
	graphics->DrawString(L"Unfair", -1, &font, PointF(width / 3, height/10), &cyan);
	graphics->DrawString(str3.str().c_str(), -1, &numfont, PointF(width / 3, height / 20), &cyan);
	

}