/**
* \file UMLInheritanceBad.h
*
* \author Josiah Klann
*
* Class the describes a bad inheritance uml item
*/

#pragma once
#include "UMLInheritance.h"

/** Class that contains info of a bad inheritance uml item
*/
class CUMLInheritanceBad :
	public CUMLInheritance
{
public:
	CUMLInheritanceBad() = delete; ///default ctor (deleted)

	/** CTOR for uml bad inheritance
	* \param base Name of base class
	* \param derived Name of derived class
	* \param error Error of this inheritance
	* \param direction Direction of the inheritance arrow
	*/
	CUMLInheritanceBad(std::wstring base, std::wstring derived, std::wstring error, std::wstring direction) : CUMLInheritance(base, derived) { mError = error; mDirection = direction; }

	/** Gets error for bad uml
	* \return mError the error
	*/
	std::wstring GetError() { return mError; }

	/** Gets the direction for bad uml
	* \return mDirection the direction
	*/
	std::wstring GetDirection() { return mDirection; }

private:
	/// The error with this uml
	std::wstring mError;
	/// The direction of inheritance error of uml
	std::wstring mDirection; 

};

