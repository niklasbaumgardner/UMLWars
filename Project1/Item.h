/**
* \file Item.h
*
* \author Will Lennon
*
* Item base class for all the objects in the game
*/

#pragma once
#include <memory>
#include "VisitorItem.h"
using namespace Gdiplus;

/**
* Lays out all operations possible on items belonging to the game
*/
class CGame;
/**
 * Where the fish exist in the aquarium
 */
class CItem
{
public:
	/// Default constructor (disabled)
	CItem() = delete;

	/// Copy constructor (disabled)
	CItem(const CItem&) = delete;

	virtual ~CItem();

	/** gets the game member
	* \returns mGame the game member
	*/
	virtual CGame* GetGame() { return mGame; }

	/** The X location of the item
	* \returns X location in pixels 
	*/
	double GetX() const { return mX; }

	/** The Y location of the item
	* \returns Y location in pixels 
	*/
	double GetY() const { return mY; }

	/** Gets the angle of rotation for the item
	* \returns angle of the item
	*/
	double GetAngle() { return mAngle; }

	/** Sets the x position of an item
	* \param x X position setting to
	*/
	void SetX(double x) { mX = x; }

	/** Sets the y position of an item
	* \param y Y position setting to
	*/
	void SetY(double y) { mY = y; }
	
	/** Sets the angle of the item
	* \param angle Angle being set
	*/
	void SetAngle(double angle) { mAngle = angle; }

	/**Set the item location
	* \param x X location
	* \param y Y location
	*/
	virtual void SetLocation(double x, double y) { mX = x; mY = y; }
	
	/** Draw this item
	* \param graphics Graphics device to draw on
	*/
	virtual void Draw(Gdiplus::Graphics* graphics) {}

	/**
	* Accepts a visitor
	* \param visitor Reference to CItemVisitor object
	*/
	virtual void Accept(CVisitorItem* visitor) {}

	/** updates the item
	* \param elapsed the time elapsed
	*/
	virtual void Update(double elapsed) {}

	/** Checks for good uml
	* \returns bool if good uml
	*/
	virtual bool GetGood() { return false; }

	/** 
	* \returns The game the item is associated with
	*/
	virtual double CalcAngle(double x);

	/** Gets the width of an item
	* \returns width of item
	*/
	virtual int GetWid() { return 0; }

	/** Gets the height of an item
	* \returns height of item
	*/
	virtual int Height() { return 0; }

protected:
	/// CTOR for an
	CItem(CGame* game); 
	/// item image
	std::unique_ptr<Gdiplus::Bitmap> mImage; 
	/// current angle of rotation of item
	double mAngle = 0; 

private:
	/// game item is associated with
	CGame* mGame; 
	/// x location (center of item)
	double mX = 0;
	/// y location (center of item)
	double mY = 0; 
	
	

};


