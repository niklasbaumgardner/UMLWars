/**
* \file VisitorItemScoreboard.cpp
*
* \author Niklas Baumgardner
*/

#include "pch.h"
#include "VisitorItemScoreboard.h"
#include "ItemScoreboard.h"

/** Add correct score to scoreboard */
void CVisitorItemScoreboard::AddCorrect()
{
	mScoreboard->addCorrect();
}

/** Add missed score to scoreboard */
void CVisitorItemScoreboard::AddMissed()
{
	mScoreboard->addMissed();
}

/** Add unfair score to scoreboard */
void CVisitorItemScoreboard::AddUnfair()
{
	mScoreboard->addUnfair();
}