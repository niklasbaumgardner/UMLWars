/**
* \file ItemSharpie.h
*
* \author Niklas Baumgardner
*
* The implementation of a sharpie item in the game
*/

#pragma once
#include "Item.h"
#include "VisitorItem.h"
#include "Vector.h"
#include "ItemUML.h"
#include <string>
#include <memory>

/**
* Class for sharpie
*/
class CItemSharpie : public CItem
{
public:
	CItemSharpie(CGame* game);

	virtual void Draw(Gdiplus::Graphics* graphics) override;
	virtual void Accept(CVisitorItem* visitor) override { visitor->VisitSharpie(this); }

	virtual void Update(double) override;

	/*
	* Sets the velocity vector 
	* \param v velocity
	*/
	void SetVelocity(CVector v) { mV = v; }
	void ReverseVelocity();

	/** Gets the velocity
	* \returns velocity vector of the sharpie
	*/
	CVector GetVelocity() { return mV; }

	/*
	*Sets the position vector of the sharpie 
	* \param pos vector of position
	*/
	void SetPosition(CVector pos) { this->SetLocation(pos.X(), pos.Y()); }
	/*
	*calculates angle
	*/
	virtual double CalcAngle(double) override;
	/*
	*sharpie hittest
	*/
	bool HitTest(std::shared_ptr<CItem>);
	/*
	*resets sharpie
	*/
	void Reset(double, double);


private:

	/// Rotation conversion
	double mRotation = 57.295779513;
	/// The sharpie's velocity vector
	CVector mV;  
	/// Position of the sharpie as a vector
	CVector mP;  

};

