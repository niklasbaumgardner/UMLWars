/**
 * \file VisitorItemHarold.cpp
 *
 * \author Christopher Beeman
*/

#include "pch.h"
#include "VisitorItemHarold.h"
#include "Item.h"

using namespace std;

/** Visits the harold object
* \param harold The harold object
*/
void CVisitorItemHarold::VisitHarold(CItemHarold* harold)
{
	mHarold = harold;
	mX = harold->GetX();
	mY = harold->GetY();
	mHarold = harold;
}