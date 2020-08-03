/**
* \file VisitorItemHarold.h
*
* \author Christopher Beeman
*
* Visits Harold to add a new pen after being shot
*/

#pragma once
#include "VisitorItem.h"
#include "ItemHarold.h"
#include "Game.h"

/**
* Harold visitor
*/
class CVisitorItemHarold : public CVisitorItem
{
public:
	virtual void VisitHarold(CItemHarold*) override;

	void NewPen();

	/**
	* \returns X position of Harold
	*/
	double GetX() { return mY; }

	/**
	* \returns Y position of harold
	*/
	double GetY() { return mY; }

	//void SetCharacter(std::wstring  character) { mHarold->SetCharacter(character); }

private:
	double mX = 0;
	double mY = 0;
};

