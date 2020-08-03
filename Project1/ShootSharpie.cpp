/**
* \file ShootSharpie.cpp
*
* \author Christopher Beeman
*/

#include "pch.h"
#include "VisitorItemSharpieShoot.h"
#include <math.h>

/**
* Visits the sharpie item
* \param sharpie Sharpie being shot
*/
void CVisitorItemSharpieShoot::VisitSharpie(CItemSharpie* sharpie)
{
	mSharp = sharpie;
}

/**
* Shoots the sharpie
* \param x X position of mouse when shot
* \param y Y position of mouse when shot
*/
void CVisitorItemSharpieShoot::Shoot(double x, double y)
{
	if (!mSharp->GetVelocity().X() || !mSharp->GetVelocity().Y())
	{
		double angle = mSharp->CalcAngle(x);
		CVector V(mSpeed * -cos(angle), mSpeed * sin(angle));
		mSharp->SetVelocity(V);
	}
}