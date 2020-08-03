/**
* \file VisitorItemUMLCheck.cpp
*
* \author Josiah Klann
*/

#include "pch.h"
#include "VisitorItemUMLCheck.h"

/** Visits the uml item
* \param itemUML The uml being visited
*/
void CVisitorItemUMLCheck::VisitUML(CItemUML* itemUML)
{
	mIsUML = true;
	mUml = itemUML;
}
