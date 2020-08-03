/**
* \file VisitorItemUMLCheck.h
*
* \author Josiah Klann
*
* Visitor for uml
*/

#pragma once
#include "VisitorItem.h"
#include "ItemUML.h"

/**
* Visitor child that visits uml items
*/
class CVisitorItemUMLCheck : public CVisitorItem
{
public:
	/** Returns if a uml object was visited
	* \return bool
	*/
	bool IsUML() { return mIsUML; }

	virtual void VisitUML(CItemUML* itemUML) override;

	/** Resets uml visitor if new uml object visited */
	void Reset() { mIsUML = false; }

	/** Gets y position of the uml
 	* \return y position
	*/
	double GetY() { return mUml->GetY(); }

	/** Gets height of the uml
	* \returns height
	*/
	double Height() { return mUml->Height(); }
	
	/** Checks if the uml being visited has been hit
	* \returns bool
	*/
	bool IsHit() { return mUml->IsHit(); }

	/** Checks if the uml being visited has been missed
	* \returns bool
	*/
	bool IsMissed() { return mUml->IsMissed(); }

	/** Sets the hit flag of an item */
	void SetHit() { mUml->SetHit(); }
	
	/** Sets the missed flag of an item */
	void SetMissed() { mUml->SetMissed(); }

	/** Gets the timer for the uml object
	* \returns The timer for a uml object
	*/
	double GetTimer() { return mUml->GetTimer(); }

	/** Checks for good or bad uml
	* \returns bool
	*/
	bool GetGood() { return mUml->GetGood(); }

private:
	/// Flag to show visitor object was accepted
	bool mIsUML = false;
	/// Uml object currently being visited
	CItemUML* mUml; 
};

