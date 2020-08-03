/**
* \file ItemHarold.cpp
*
* \author Will Lennon
*/

#include "pch.h"
#include "Game.h"
#include "ItemHarold.h"
#include <string>
using namespace std;
using namespace Gdiplus;

/// Image name
const wstring HaroldImageName = L"../images/harold.png"; 
/// Angle conversion constant
const double RtoD = 57.295779513;
/// pi
const double pi = 3.14159265358979;

/** Harold item constructor
* \param game game
*/
CItemHarold::CItemHarold(CGame* game) : CItem(game)
{
	mCharacter = HaroldImageName;
	mImage = unique_ptr<Bitmap>(Bitmap::FromFile(mCharacter.c_str()));
	if (mImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += HaroldImageName;
		AfxMessageBox(msg.c_str());
	}
	
}

/**
 * Draw this item
 * \param graphics Graphics device to draw on
 */
void CItemHarold::Draw(Gdiplus::Graphics* graphics)
{
	mImage = unique_ptr<Bitmap>(Bitmap::FromFile(mCharacter.c_str()));
	
	double width = mImage->GetWidth();
	double height = mImage->GetHeight();

	double x = GetX();
	double y = GetY();

	// Rotates based on mouse position
	CGame* game = CItem::GetGame();
	double mouseX = game->GetMouseX();
	double mouseY = game->GetMouseY();
	
	// Calculate the angle
	mAngle = CalcAngle(mouseX);
	
	// Rotates image and draws
	auto state = graphics->Save();
	graphics->TranslateTransform((float)x, (float)y);
	graphics->RotateTransform((float)(-mAngle * RtoD));
	graphics->DrawImage(mImage.get(), -width/2,-height/2, (float)width, (float)height);
	graphics->Restore(state);
}

