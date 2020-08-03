/**
* \file ShootSharpie.h
*
* \author Christopher Beeman
*
* Visitor that shoots the sharpie out of harold's hand
*/

#pragma once
#include "VisitorItem.h"
#include "ItemSharpie.h"
#include "Vector.h"


/**
* Visits the sharpie object and shoots it from Harolds hand
*/
class CVisitorItemSharpieShoot :public CVisitorItem
{
public:
	virtual void VisitSharpie(CItemSharpie*) override;
	
	void Shoot(double, double);

	/** Get x position of sharpie
	* \returns X position of sharpie
	*/
	double GetX() { return mSharp->GetX(); }

	/** Get y position of sharpie
	* \returns y position of sharpie
	*/
	double GetY() { return mSharp->GetY(); }

	/** Get sharpie object
	* \returns sharpie
	*/
	CItemSharpie* GetSharpItem() { return mSharp; }


private:

	CItemSharpie* mSharp; /// The sharpie being visited
	 
	double mSpeed = 1000; /// Speed of the sharpie
};

