/**
* \file Emitter.h
*
* \author Christopher Beeman
*
* This class will emit UML into our game
*/

#pragma once
#include "ItemUML.h"
#include "XmlNode.h"
#include <memory>
#include <vector>
#include<map>
#include "UMLInheritance.h"
#include "UMLInheritanceBad.h"

using namespace xmlnode;

/** Emitter class */
class CEmitter
{
public:
	CEmitter() {};
	void Load(std::wstring& filename);
	void NameXml(std::shared_ptr<xmlnode::CXmlNode>& node);
	void AttributeXml(std::shared_ptr<xmlnode::CXmlNode>& node);
	void OperationXml(std::shared_ptr<xmlnode::CXmlNode>& node);
	void InheritanceXml(std::shared_ptr<xmlnode::CXmlNode>& node);

	void GenerateUML(double, CGame*);

	void ToXmlItems();
	void ToBadXmlItems();
	

	//void Emit();
	// new
private:
	/// stores names
	std::vector<std::wstring> mNames;
	/// stores bad names
	std::map<std::wstring, std::wstring> mBadNames;
	/// stores attributes
	std::vector<std::wstring> mAttributes;
	/// stores bad attributes
	std::map<std::wstring, std::wstring> mBadAttributes;
	/// stores operstions
	std::vector<std::wstring> mOperations;
	/// stores bad operations
	std::map<std::wstring, std::wstring> mBadOperations;
	/// stores inheritance
	std::vector<CUMLInheritance> mInheritance;
	/// stores bad inheritance
	std::vector<CUMLInheritanceBad> mBadInheritance;

	/// stores xml items
	std::vector<std::vector<std::wstring>> mXmlItems;
	/// stores bad xml items
	std::vector<std::map<std::wstring, std::wstring>> mBadXmlItems;
	/// probability of good vs bad
	double mProbBad = 1;
};

