/**
 * \file ItemScoreboard.h
 *
 * \author Niklas Baumgardner
 *
 * 
 */

#pragma once

#include "Item.h"
#include <vector>
#include <string>
#include <memory>

/** Class for scoreboard */
class CItemScoreboard : public CItem
{
public:
	CItemScoreboard(CGame* game);
	void Draw(Gdiplus::Graphics* graphics);

	/*
	* accepts the visitor item
	\param visitor visitor to scoreboard
	*/
	virtual void Accept(CVisitorItem* visitor) override { visitor->VisitScoreboard(this); }
	
	/** Adds to the correct score */
	void addCorrect() { ++mCorrect; }

	/** Adds to the missed score */
	void addMissed() { ++mMissed; }

	/** Adds to the unfair score */
	void addUnfair() { ++mUnfair; }

private:
	int mCorrect = 0; /// The the score of correct uml hits
	int mMissed = 0;  /// Number of missed uml that should have been hit
	int mUnfair = 0;  /// Number of unfair gradings
};

