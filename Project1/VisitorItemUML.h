/**
* \file VisitorUML.h
*
* \author Christopher Beeman
*
* Visitor for uml items
*/

#pragma once
#include "VisitorItem.h"
#include <vector>
#include "ItemSharpie.h"
#include "ItemUML.h"
/**
* Implementation that will visit all UML belonging to the game
*/
class CVisitorItemUML : public CVisitorItem
{
public:
	virtual void VisitUML(CItemUML* uml) override;

	CItemUML* HitTest(CItemSharpie*);
	
	/** Gets the uml item that most recently has been hit by the pen
	* \returns uml item
	*/
	CItemUML* GetItem() { return mItemUML; }

private:
	std::vector<CItemUML*> mUML; /// Container for all uml in the game

	CItemUML* mItemUML;

};

