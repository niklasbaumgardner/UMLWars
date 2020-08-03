/**
* \file VisitorUML.cpp
*
* \author Christopher Beeman
*/

#include "pch.h"
#include "VisitorItemUML.h"

/**
* Visits a UML Item
* \param uml Item being visited
*/
void CVisitorItemUML::VisitUML(CItemUML* uml)
{
	mUML.push_back(uml);
	mItemUML = uml;
}

/**
* Determines if the pen came in contact with a uml item
* \param sharpie The games sharpie item that is being shot
* \returns bool If sharpie hit the uml
*/
CItemUML* CVisitorItemUML::HitTest(CItemSharpie* sharpie)
{
	for (auto uml : mUML)
	{
		//if (sharpie->HitTest(uml))
		//{
		//	return uml;
		//}
	}
	return nullptr;
}

