/**
 * \file ItemHarold.h
 *
 * \author Will Lennon
 *
 * Harold object that plays the game
 */

#pragma once
#include "Item.h"
#include "VisitorItem.h"
#include "ItemSharpie.h"
#include <string>
#include <memory>

/** Class for Harold */
class CItemHarold : public CItem
{
public:
	CItemHarold(CGame* game);
	virtual void Draw(Gdiplus::Graphics* graphics);

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CVisitorItem* visitor) override { visitor->VisitHarold(this); }

	/** Sets the character image
	* \param character The file name of the character image
	*/
	virtual void SetCharacter(std::wstring character) { mCharacter = character; }

private:
	/// File to draw image
	std::wstring mCharacter;
};



