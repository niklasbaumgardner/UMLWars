/**
* \file UMLInheritance.h
*
* \author Josiah Klann
*
* Class the describes a inheritance uml item
*/

#pragma once

#include<string>

/** Class that contains info of a inheritance uml item
*/
class CUMLInheritance
{
public:
	CUMLInheritance() = delete; /// default ctor (deleted)

	/**
	* CTOR for uml inheritance
	* \param base Name of base class
	* \param derived Name of derived class
	*/
	CUMLInheritance(std::wstring base, std::wstring derived) { mBase = base; mDerived = derived; }

	/** Gets the name of the base class for this inheritance
	* \return mBase Name of the base class for this inheritance
	*/
	virtual std::wstring GetBase() { return mBase; }

	/** Gets the name of the derived class for this inheritance
	* \return mDerived Name of the derived class for this inheritance
	*/
	virtual std::wstring GetDerived() { return mDerived; }

private:
	/// Name of the base class for this inheritance
	std::wstring mBase; 
	/// Name of the derived class for this inheritance
	std::wstring mDerived;
};

