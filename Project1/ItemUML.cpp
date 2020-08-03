/**
* \file ItemUML.cpp
*
* \author Christopher Beeman
*/

#include "pch.h"
#include "ItemUML.h"
#include "Game.h"
#include <math.h>
#include <sstream>

using namespace std;
using namespace Gdiplus;
/// Max x speed for UML
const double xSpeedMax = 50;
/// Max y speed for UML
const double ySpeedMax = 100;

/**
 * Constructor
 * \param game
 */
CItemUML::CItemUML(CGame* game) : CItem(game)
{
	//LARGE_INTEGER timeNiklas;
	QueryPerformanceCounter(&timeNiklas);

	int x = (((double)rand() / RAND_MAX) * GetGame()->GetWidth()) - (GetGame()->GetWidth()) / 2;
	SetX(x - 100.0);
	SetY(0);
	double xSpeed = ((double)rand() / RAND_MAX)* (xSpeedMax) * pow(-1, (int)rand() % 2);
	double ySpeed = 50 + ((double)rand() / RAND_MAX) * ySpeedMax;
	increaseSpeed++;
	SetSpeed(((double)rand() / RAND_MAX) * (xSpeedMax) * pow(-1, (int)rand() % 2) + (increaseSpeed / 500), 50 + ((double)rand() / RAND_MAX) * ySpeedMax + (increaseSpeed / 100));
	
}

/**
* Draws the sharpie object
* \param graphics Context the sharpie being drawn to
*/
void CItemUML::Draw(Gdiplus::Graphics* graphics)
{
	double h;
	double counter = 1;
	double BiggestWidth;
	double w;
	double sumH;
	double opLine;
	RectF size;
	Pen pen(Color(0, 0, 0), 1);
	PointF origin(0.0f, 0.0f);
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 12);
	graphics->MeasureString(mName.c_str(), -1, &font, origin, &size);
	h = size.Height;
	w = size.Width;
	sumH = h;
	BiggestWidth = size.Width;
	for (int i = 0; i < mAttributes.size(); i++)
	{
		graphics->MeasureString(mAttributes[i].c_str(), -1, &font, origin, &size);
		if (size.Width > BiggestWidth)
		{
			BiggestWidth = size.Width;
		}
		sumH = size.Height + sumH;
	}
	opLine = sumH;
	for (int i = 0; i < mOperations.size(); i++)
	{
		graphics->MeasureString(mOperations[i].c_str(), -1, &font, origin, &size);
		if (size.Width > BiggestWidth)
		{
			BiggestWidth = size.Width;
		}
		sumH = size.Height + sumH;
	}
	graphics->DrawRectangle(&pen, GetX(), GetY(), mWid = BiggestWidth + 5, mHeight = sumH + 10);

	SolidBrush brush(Color(255,255,193));
	//SolidBrush brush(Color(rand() % 256, rand() % 256, rand() % 256));
	SolidBrush wordBrush(Color(0, 0, 0));
	graphics->FillRectangle(&brush, GetX() + 1, GetY() + 1, mWid - 2, mHeight - 2);
	graphics->DrawLine(&pen, (int)GetX(), (int)(GetY() + 20), GetX() + mWid, GetY() + 20);
	if (mOperations.size() > 0)
	{
		graphics->DrawLine(&pen, (int)GetX(), (int)(GetY() + opLine), GetX() + mWid, GetY() + opLine);
	}
	graphics->DrawString(mName.c_str(), -1, &font, PointF(GetX() + mWid / 2 - w / 2, GetY()), &wordBrush);
	for (int i = 0; i < mAttributes.size(); i++)
	{
		graphics->DrawString(mAttributes[i].c_str(), -1, &font, PointF(GetX(), GetY() + counter * h), &wordBrush);
		counter++;
	}
	for (int i = 0; i < mOperations.size(); i++)
	{
		graphics->DrawString(mOperations[i].c_str(), -1, &font, PointF(GetX(), GetY() + counter * h), &wordBrush);
		counter++;
	}




	if (mHasInheritance)
	{
		int NewBiggestWidth = 0;
		counter = 1;
		graphics->MeasureString(mInheritance.c_str(), -1, &font, origin, &size);
		h = size.Height;
		w = size.Width;
		NewBiggestWidth = w;
		int oldSumH = sumH;
		sumH = sumH + h;
		for (int i = 0; i < mInheritanceAttributes.size(); i++)
		{
			graphics->MeasureString(mInheritanceAttributes[i].c_str(), -1, &font, origin, &size);
			if (size.Width > NewBiggestWidth)
			{
				NewBiggestWidth = size.Width;
			}
			sumH = size.Height + sumH;
		}
		
		opLine = sumH+100+20;
		for (int i = 0; i < mInheritanceOperations.size(); i++)
		{
			graphics->MeasureString(mInheritanceOperations[i].c_str(), -1, &font, origin, &size);
			if (size.Width > NewBiggestWidth)
			{
				NewBiggestWidth = size.Width;
			}
			sumH = size.Height + sumH;
		}
		
		graphics->DrawRectangle(&pen, GetX() + mWid / 2 - NewBiggestWidth / 2, GetY() + 100+oldSumH + 5, (int)NewBiggestWidth, (int)sumH -oldSumH + 10);
		SolidBrush brush(Color(255, 255, 193));
		SolidBrush wordBrush(Color(0, 0, 0));
		graphics->FillRectangle(&brush, GetX() + 2 + mWid / 2 - NewBiggestWidth / 2, GetY() + oldSumH + 100 + 6, (int)NewBiggestWidth - 3, (int)sumH - oldSumH + 8);
		graphics->DrawLine(&pen, (int)(GetX() + mWid / 2 - NewBiggestWidth / 2), (int)(GetY() + oldSumH + h + 100), GetX() + mWid / 2 + NewBiggestWidth / 2, GetY() + oldSumH + h + 100);
		if (mInheritanceOperations.size() > 0)
		{
			graphics->DrawLine(&pen, (int)(GetX() + mWid/2 - NewBiggestWidth / 2), (int)(GetY() + opLine-h+2), GetX() + mWid / 2 + NewBiggestWidth / 2, GetY() + opLine-h+2);
		}
		graphics->DrawString(mInheritance.c_str(), -1, &font, PointF(GetX() + mWid / 2 - w / 2, GetY() + mHeight + 93), &wordBrush);
		for (int i = 0; i < mInheritanceAttributes.size(); i++)
		{
			graphics->DrawString(mInheritanceAttributes[i].c_str(), -1, &font, PointF(GetX() + mWid / 2 - NewBiggestWidth / 2, GetY() + 100+ oldSumH + 3 + counter*h), &wordBrush);
			counter++;
		}
		for (int i = 0; i < mInheritanceOperations.size(); i++)
		{
			graphics->DrawString(mInheritanceOperations[i].c_str(), -1, &font, PointF(GetX() + mWid / 2 - NewBiggestWidth / 2, GetY() + 100 +oldSumH + 5 + counter * h), &wordBrush);
			counter++;
		}
		
		//arrow
		if(mArrowDown)
		{
			//line
			graphics->DrawLine(&pen, PointF(GetX() + mWid / 2, GetY() + mHeight + 20), PointF(GetX() + mWid / 2, GetY() + mHeight + 100));
			graphics->DrawLine(&pen, PointF(GetX() + mWid / 2 - 10, GetY() + mHeight + 20), PointF(GetX() + mWid / 2 + 10, GetY() + mHeight + 20));
			graphics->DrawLine(&pen, PointF(GetX() + mWid / 2 - 10, GetY() + mHeight + 20), PointF(GetX() + mWid / 2, GetY() + mHeight));
			graphics->DrawLine(&pen, PointF(GetX() + mWid / 2 + 10, GetY() + mHeight + 20), PointF(GetX() + mWid / 2, GetY() + mHeight));
		}
		else
		{
			//line
			graphics->DrawLine(&pen, PointF(GetX() + mWid / 2, GetY() + mHeight + 80), PointF(GetX() + mWid / 2, GetY() + mHeight));
			graphics->DrawLine(&pen, PointF(GetX() + mWid / 2 - 10, GetY() + mHeight + 80), PointF(GetX() + mWid / 2 + 10, GetY() + mHeight + 80));
			graphics->DrawLine(&pen, PointF(GetX() + mWid / 2 - 10, GetY() + mHeight + 80), PointF(GetX() + mWid / 2, GetY() + mHeight+96));
			graphics->DrawLine(&pen, PointF(GetX() + mWid / 2 + 10, GetY() + mHeight+80), PointF(GetX() + mWid / 2, GetY() + mHeight+96));
		}
		mHeight = mHeight + 100 + mHeight;
	}

	SolidBrush wordBrush2(Color(255, 0, 0));
	SolidBrush green(Color(6, 161, 89));
	Gdiplus::Font font2(&fontFamily, 20);
	if (mHit)
	{
		if (!mGood)
		{
			graphics->DrawString(mErrorMessage.c_str(), -1, &font2, PointF(GetX(), GetY()+mHeight/2), &green);
		}
		else
		{
			graphics->DrawString(L"Unfair!", -1, &font2, PointF(GetX(), GetY()+mHeight/2), &wordBrush2);
		}
	}
}

/**
* Updates the UML
* \param elapsed Elapsed time since last time window drawn
*/
void CItemUML::Update(double elapsed)
{
	if (!mHit)
	{
		SetLocation(GetX() + mSpeedX * elapsed, GetY() + mSpeedY * elapsed);

		// Reverse speed if the uml objects hit the sides
		if (mSpeedX > 0 && GetX() >= GetGame()->GetWidth() - 600 - (this->mWid))
		{
			mSpeedX = -mSpeedX;
		}

		if (mSpeedX < 0 && GetX() <= 450 + this->mWid - GetGame()->GetWidth())
		{
			mSpeedX = -mSpeedX;
		}
	}
	else
	{
		// Updates the uml timer to eventually be removed
		mTimer = mTimer - elapsed;
	}

}

