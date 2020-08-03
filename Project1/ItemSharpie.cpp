/**
* \file ItemSharpie.cpp
*
* \author Niklas Baumgardner
*/

#include "pch.h"
#include "ItemSharpie.h"
#include "Game.h"
#include <string>

using namespace std;
using namespace Gdiplus;
/// Image name
const wstring SharpieImageName = L"../images/redpen.png";
/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;
/// pi
const double pi = 3.14159265358979;

/** Sharpie constructor
*/
CItemSharpie::CItemSharpie(CGame* game) : CItem(game)
{
	mImage = unique_ptr<Bitmap>(Bitmap::FromFile(SharpieImageName.c_str()));
	if (mImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to oSharpie ");
		msg += SharpieImageName;
		AfxMessageBox(msg.c_str());
	}
}

/**
* Draws the sharpie object
* \param graphics Context the sharpie being drawn to
*/
void CItemSharpie::Draw(Gdiplus::Graphics* graphics)
{
	double width = mImage->GetWidth();
	double height = mImage->GetHeight();

	double x = GetX();
	double y = GetY();

	CGame* game = CItem::GetGame();
	double mouseX = game->GetMouseX();
	double mouseY = game->GetMouseY();

	//mAngle = -mouseX * pi / 2000 - 1.078;
	if (!mV.X() && !mV.Y())
	{
		mAngle = this->CalcAngle(mouseX);
	}

	auto state = graphics->Save();
	graphics->TranslateTransform((float)x, (float)y);
	graphics->RotateTransform((float)(-mAngle * RtoD));
	graphics->DrawImage(mImage.get(), -60.0, -60.0, (float)width, (float)height);
	graphics->Restore(state);



}

/** Updates the position and drawing of sharpie
* \param elapsed Elapsed time since last time window drawn
*/
void CItemSharpie::Update(double elapsed)
{
	CGame* game = this->GetGame();
	if (mV.X() || mV.Y())
	{
		mP.SetX(GetX());
		mP.SetY(GetY());
		CVector newPos = mP + mV * elapsed;
		this->SetLocation(newPos.X(), newPos.Y());

	}
}

/** Calculates the new angle of the sharpiee
* \param x X location of the mouse
*/
double CItemSharpie::CalcAngle(double x)
{
	double angle = -x * pi / 1100 - 1.078 + .9;
	return angle;
}

/**
* Determines if two items come in contact with one another
* \param uml pointer to uml object
* \returns bool Whether or not a hit occured
*/
bool CItemSharpie::HitTest(std::shared_ptr<CItem> uml)
{
	double x = uml->GetX();
	double y = uml->GetY();

	int UmlWidth = uml->GetWid();
	int UmlHeight = uml ->Height();

	double PenX = GetX();
	double PenY = GetY();

	// Checks if the pen is inside the dimensions of the uml box
	if (PenX+mImage->GetWidth() > x && PenY > y && (PenX) < (x+UmlWidth) && (PenY+mImage->GetHeight()) < (y+UmlHeight) && mV.X() != 0 && mV.Y() != 0)
	{
		return true;
	}
	else 
	{ 
		return false; 
	}

}

/**
* Resets the pen location and velocity
*/
void CItemSharpie::Reset(double x, double y)
{
	CVector newV(0, 0);
	SetVelocity(newV);
	SetLocation(x, y);
}

/**
* Reverses the velocity of the sharpie
*/
void CItemSharpie::ReverseVelocity()
{
	double vx = mV.X();
	CVector newV(-vx, mV.Y());
	SetVelocity(newV);
}