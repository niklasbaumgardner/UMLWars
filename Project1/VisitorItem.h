/**
 * \file ItemVisitor.h
 *
 * \author Josiah Klann
 *
 * Base visitor class for items
 */

#pragma once


// Forward References to all item types
class CItemScoreboard;
class CItemHarold;
class CItemSharpie;
class CItemUML;

/**
* Base visitor class for items
*/
class CVisitorItem
{
public:
	/**
	* CItem Visitor Destructor
	*/
	virtual ~CVisitorItem() {}

	/**
	* Visit a CScoreboard item
	* \param scoreboard Reference to CScoreboard object
	*/
	virtual void VisitScoreboard(CItemScoreboard* scoreboard) {}

	/**
	* Visit a CHarold item
	* \param harold Reference to CHarold object
	*/
	virtual void VisitHarold(CItemHarold* harold) {}

	/**
	* Visit a CSharpie item
	* \param sharpie Reference to sharpie object
	*/
	virtual void VisitSharpie(CItemSharpie* sharpie) {}

	/**
	* Visit a UML item
	* \param uml Reference to a uml object
	*/
	virtual void VisitUML(CItemUML* uml) {}

};

