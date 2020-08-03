/**
 * \file VisitorItemScoreboard.h
 *
 * \author Niklas Baumgardner
 *
 * Visitor for the scoreboard
 */

#pragma once
#include "VisitorItem.h"

/** Visitor for scoreboard */
class CVisitorItemScoreboard : public CVisitorItem
{
public:
	virtual void VisitScoreboard(CItemScoreboard* scoreboard) { mScoreboard = scoreboard; };
	
	void AddCorrect();
	
	void AddMissed();

	void AddUnfair();

private:
	CItemScoreboard* mScoreboard; /// The scoreboard being visited
};

