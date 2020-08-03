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
class CHarold;
class CSharpie;

/**
* Base visitor class for items
*/
class CItemVisitor
{
public:
	/**
	* CItem Visitor Destructor
	*/
	virtual ~CItemVisitor() {}

	/**
	* Visit a CScoreboard item
	* \param scoreboard Reference to CScoreboard object
	*/
	virtual void VisitScoreboard(CItemScoreboard* scoreboard) {}

	/**
	* Visit a CHarold item
	* \param harold Reference to CHarold object
	*/
	virtual void VisitHarold(CHarold* harold) {}

	/**
	* Visit a CSharpie item
	* \param sharpie Reference to sharpie object
	*/
	virtual void VisitSharpie(CSharpie* sharpie) {}

};

