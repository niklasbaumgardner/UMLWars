/**
 * \file VisitorItemHaroldRotator.h
 *
 * \author Josiah Klann
 *
 *  Visitor that rotates harold
 */

#pragma once
#include "ItemVisitor.h"
#include "ItemHarold.h"

/**
* Visitor class that rotates a harold item
*/
class CVisitorItemHaroldRotator : public CItemVisitor
{
public:
	void VisitHarold(CItemHarold* harold);
};

