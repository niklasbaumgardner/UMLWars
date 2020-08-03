/**
* \file Item.cpp
*
* \author Will Lennon
*/

#include "pch.h"
#include "Item.h"
#include "Game.h"

/// Value of pie to calculate an angle
const double pi = 3.14159265358979;

using namespace Gdiplus;

/** Constructor
* \param game The game this item is a member of
*/
CItem::CItem(CGame* game) : mGame(game)
{
}

/**
 * Destructor
 */
CItem::~CItem()
{
}

/**
* Calculates the angle the item is rotated
* \param x X position of the mouse to calculate based off
* \returns angle of rotation
*/
double CItem::CalcAngle(double x)
{

	double angle = -x * pi / 1100 + .9;
	return angle;
}

