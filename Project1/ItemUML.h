/**
* \file ItemUML.h
*
* \author Christopher Beeman
*
* Implementation of UML that is being graded
*/

#pragma once
#include "Item.h"
#include "Vector.h"
#include "VisitorItem.h"
#include <string>
#include <vector>

/**
* Class that will handle all of the UML
*/
class CItemUML : public CItem
{
public:
	CItemUML(CGame* game);
	virtual void Update(double) override;
	virtual void Draw(Gdiplus::Graphics* graphics) override;
	/**
	* set uml speed
	* \param x x speed
	* \param y y speed
	*/
	void SetSpeed(double x, double y) { mSpeedX = x; mSpeedY = y; }
	/** Get the x speed of uml
	* \returns x speed
	*/
	double GetSpeedX() { return mSpeedX; }
	/** Get the y speed of the object
	* \returns y speed
	*/
	double GetSpeedY() { return mSpeedY; }
	/*
	*accepts item to visitor
	* \param visitor visitor
	*/
	virtual void Accept(CVisitorItem* visitor) override { visitor->VisitUML(this); }

	/** Get the width of the uml object
	* \returns width of the object
	*/
	virtual int GetWid() override { return mWid; } 

	/** Get the height of the uml object
	* \returns the height of the object
	*/
	virtual int Height() override { return mHeight; }
	/** Get the good of the uml
	* \returns goodness
	*/
	virtual bool GetGood() override { return mGood; }
	/**
	* set goodness
	* \param good good
	*/
	void SetGood(bool good) { mGood = good; }
	/**
	* set name
	* \param name name
	*/
	void SetNameText(std::wstring text) { mName = text; }
	/**
	* set inheritance
	* \param inheritance inheritance
	*/
	void SetHasInheritance(bool hasinhert) { mHasInheritance = hasinhert; }
	/**
	* set hasAttributes
	* \param hasinhert hasinhert
	*/
	void SetAttributes(std::vector<std::wstring> attributes) { mAttributes = attributes; }
	/**
	* set Operations
	* \param operations Operations
	*/
	void SetOperations(std::vector<std::wstring> operations) { mOperations = operations; }
	/**
	* set inheritance
	* \param inheritance inheritance
	*/
	void SetInheritance(std::wstring inheritance) { mInheritance = inheritance; }
	/**
	* set ErrorMessage
	* \param error error
	*/
	void SetErrorMessage(std::wstring error) { mErrorMessage = error; }
	/**
	* set Arrow
	* \param up up
	*/
	void SetArrow(bool up) { mArrowDown = up; }
	/**
	* set InheritanceOperations
	* \param operations operations
	*/
	void SetInheritanceOperations(std::vector<std::wstring> operations) { mInheritanceOperations = operations; }
	/**
	* set InheritanceAttributes
	* \param attributes attributes
	*/
	void SetInheritanceAttributes(std::vector<std::wstring> attributes) { mInheritanceAttributes = attributes; }

	/** Sets hit flag to true */
	void SetHit() { mHit = true; }

	/** Sets missed flag to true */
	void SetMissed() { mMissed = true; }

	/** Determines if the item has been hit
	* \returns bool if has been hit
	*/
	bool IsHit() { return mHit; }
	/**
	* Is Missed
	* \return mMissed
	*/
	bool IsMissed() { return mMissed; }

	/** Gets the timer attribute
	* \returns the timer of the object
	*/
	double GetTimer() { return mTimer; }

private:
	/// used for generating uml at certain times
	LARGE_INTEGER timeNiklas;

	double mSpeedX; /// velocity in x direction
	double mSpeedY; /// velocity in y direction
	//const long long increaseSpeed = 0;
	/// Flag for if good uml
	bool mGood = true;
	/// Flag if the item has been hit
	bool mHit = false;
	/// Flag for if item was missed and left screen
	bool mMissed = false;  
	/// name
	std::wstring mName;
	/// attributes
	std::vector<std::wstring> mAttributes;
	/// inheritance attributes
	std::vector<std::wstring> mInheritanceAttributes;
	/// operations
	std::vector<std::wstring> mOperations;
	/// inheritance operations
	std::vector<std::wstring> mInheritanceOperations;
	/// inheritance
	std::wstring mInheritance;  
	/// Error message for bad uml
	std::wstring mErrorMessage; 
	/// if uml item has inheritance
	bool mHasInheritance = false;
	/// direction of inheritance arrow
	bool mArrowDown = true;  
	/// increase speed of uml
	long long increaseSpeed = 0;

	/// Dimensions of the uml boxes
	int mWid = 200;  
	/// height of box
	int mHeight = 200; 
	/// timer determines how much time before item removed
	double mTimer = 1; 
};


