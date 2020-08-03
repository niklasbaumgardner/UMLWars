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

	/*
	* virtual harold visitor
	* \param
	*/
	virtual void VisitHarold(CItemHarold*) override;

	/**
	* \returns X position of Harold
	*/
	double GetX() { return mX; }

	/**
	* \returns Y position of harold
	*/
	double GetY() { return mY; }

	/** Gets Harold visited
	* \returns Harold object
	*/
	CItemHarold* GetHarold() { return mHarold; }

	/** Sets the character image
	* \param character File string for character image
	*/
	void SetCharacter(std::wstring character) { mHarold->SetCharacter(character); }

private:

	double mX = 0; /// X position
	double mY = 0; /// Y position
	CItemHarold* mHarold; /// Harold visited
};

