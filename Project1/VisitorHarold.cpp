/**
* \file HaroldVisitor.cpp
*
* \author Christopher Beeman
*/

#include "pch.h"
#include "VisitorItemHarold.h"
#include "ItemSharpie.h"
#include <memory>
#include "Item.h"

using namespace std;

/**
*
*
*/
void CVisitorItemHarold::VisitHarold(CItemHarold* harold)
{
	mGame = harold->GetGame();
	mHarold = harold;
}

void CVisitorItemHarold::NewPen()
{
	double x = mHarold->GetX();
	double y = mHarold->GetY();

	shared_ptr<CItem> sharpie = make_shared<CItemSharpie>(mGame);
	sharpie->SetLocation(x, y);
	mGame->Add(sharpie);
}