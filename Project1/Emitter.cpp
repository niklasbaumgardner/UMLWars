/**
* \file Emitter.cpp
*
* \author Mason Quincy
*/

#include "pch.h"
#include "Emitter.h"
#include "Game.h"
#include <algorithm>
#include<map>

using namespace xmlnode;
using namespace std;

/**
* Loads all needed uml parts from xml file
* \param filename Name of xml file
*/
void CEmitter::Load(std::wstring& filename)
{
	// We surround with a try/catch to handle errors
	try
	{
		// Open the document to read
		shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

		//
		// Traverse the children of the root
		// node of the XML document in memory!!!!
		//
		for (auto node : root->GetChildren())
		{
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"class")
			{
				for (auto n : node->GetChildren())
				{
					if (n->GetType() == NODE_ELEMENT && n->GetName() == L"name")
					{
						NameXml(n);
					}
					if (n->GetType() == NODE_ELEMENT && n->GetName() == L"attribute")
					{
						AttributeXml(n);
					}
					if (n->GetType() == NODE_ELEMENT && n->GetName() == L"operation")
					{
						OperationXml(n);
					}
				}
			}
			else if (node->GetType() == NODE_ELEMENT && node->GetName() == L"inheritance")
			{
				for (auto n : node->GetChildren())
				{
					if (n->GetType() == NODE_ELEMENT && n->GetName() == L"inherit")
					{
						InheritanceXml(n);
					}
				}

			}
			


		}

	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}
}


/**
* Gets uml name and stores in good or bad container
* \param node Node that contains the name
*/
void CEmitter::NameXml(std::shared_ptr<xmlnode::CXmlNode>& node)
{
	for (auto nc : node->GetChildren()) 
	{
		if (nc->GetType() == NODE_TEXT) 
		{
			
			if (node->GetAttributeValue(L"bad", L"") != L"")
			{
				mBadNames.insert(pair<wstring,wstring>(nc->GetValue(), node->GetAttribute(L"bad")->GetValue()));
			}
			else
			{
				mNames.push_back(nc->GetValue());
			}
		}
	}
}

/**
* Gets uml attribute and stores in good or bad container
* \param node Node that contains the attribute
*/
void CEmitter::AttributeXml(std::shared_ptr<xmlnode::CXmlNode>& node)
{
	for (auto nc : node->GetChildren())
	{
		if (nc->GetType() == NODE_TEXT)
		{
			
			if (node->GetAttributeValue(L"bad", L"") != L"")
			{
				mBadAttributes.insert(pair<wstring, wstring>(nc->GetValue(), node->GetAttribute(L"bad")->GetValue()));
			}
			else
			{
				mAttributes.push_back(nc->GetValue());
			}
		}
	}
}

/**
* Gets uml operation and stores in good or bad container
* \param node Node that contains the operation
*/
void CEmitter::OperationXml(std::shared_ptr<xmlnode::CXmlNode>& node)
{
	for (auto nc : node->GetChildren())
	{
		if (nc->GetType() == NODE_TEXT)
		{
			if (node->GetAttributeValue(L"bad", L"") != L"")
			{
				mBadOperations.insert(pair<wstring, wstring>(nc->GetValue(), node->GetAttribute(L"bad")->GetValue()));
			}
			else
			{
				mOperations.push_back(nc->GetValue());
			}
		}
	}
}

/**
* Gets uml inheritance and stores in good or bad container
* \param node Node that contains the inheritance
*/
void CEmitter::InheritanceXml(std::shared_ptr<xmlnode::CXmlNode>& node)
{
			if (node->GetAttributeValue(L"bad", L"") != L"")
			{
				mBadInheritance.push_back(CUMLInheritanceBad(node->GetAttributeValue(L"base", L""), node->GetAttributeValue(L"derived", L""), node->GetAttributeValue(L"bad", L""), node->GetAttributeValue(L"direction", L"")));
			}
			else
			{
				mInheritance.push_back(CUMLInheritance(node->GetAttributeValue(L"base", L""), node->GetAttributeValue(L"derived", L"")));
			}
}

/** 
* adds names, attributes and operations to xml items
*/
void CEmitter::ToXmlItems() 
{
	mXmlItems.push_back(mNames);
	mXmlItems.push_back(mAttributes);
	mXmlItems.push_back(mOperations);
}

/**
* adds names, attributes and operations to bad xml items
*/
void CEmitter::ToBadXmlItems() {
	mBadXmlItems.push_back(mBadNames);
	mBadXmlItems.push_back(mBadAttributes);
	mBadXmlItems.push_back(mBadOperations);
}

/** 
* Generates UML
* \param elapsed Elapsed time since last drawn
* \param game Game object uml is being generated for
*/
void CEmitter::GenerateUML(double elapsed, CGame* game)
{
	LARGE_INTEGER timeNik;
	QueryPerformanceCounter(&timeNik);
	shared_ptr<CItemUML> uml = make_shared<CItemUML>(game);
	if (timeNik.QuadPart % 1000 < 10)
	{
		//random for bad/good probability
		int randForGood = 100;
		//if it is good then create random number
		if (uml->GetGood())
		{
			srand((unsigned)time(NULL));
			randForGood = rand() % 100;
		}
		//out of 100 if it greater then 90 then make a good name
		wstring randName;
		if (randForGood < 80) // 90 is subject to change to an actual variable
		{
			//Adding one random name
			std::vector<std::wstring> mtemp = mXmlItems[0];
			srand((unsigned)time(NULL));
			int randnum = rand() % mtemp.size();
			auto itrtemp = mtemp.begin();
			for (int i = 0; i < randnum; i++)
			{
				++itrtemp;
			}
			randName = *itrtemp;
			uml->SetNameText(randName);
		}
		//make a bad name then set mGood to false and make the rest of the variables good
		else
		{
			//Adding one random name
			std::map<std::wstring, std::wstring> mtemp = mBadXmlItems[0];
			srand((unsigned)time(NULL));
			int randnum = rand() % mtemp.size();
			auto itrtemp = mtemp.begin();
			for (int i = 0; i < randnum; i++)
			{
				++itrtemp;
			}
			randName = itrtemp->first;
			uml->SetGood(false);
			uml->SetErrorMessage(itrtemp->second);
			uml->SetNameText(randName);
		}
		//Adding zero to three random attributes
		//out of 100 if it greater then 80 then make all good attributes
		std::vector<std::wstring> randatrb;
		if (!(uml->GetGood()) || randForGood < 60)
		{
			int randquantity = rand() % 3;
			std::vector<std::wstring> randatrb;
			std::vector<std::wstring> mtempatr = mXmlItems[1];
			for (int i = 0; i < randquantity; i++)
			{
				srand((unsigned)time(NULL));
				int randnumatr = rand() % mtempatr.size();
				auto itrtempatr = mtempatr.begin();
				for (int i = 0; i < randnumatr; i++)
				{
					++itrtempatr;
				}
				randatrb.push_back(*itrtempatr);
				mtempatr.erase(itrtempatr);
			}
			uml->SetAttributes(randatrb);
		}
		else
		{
			int randquantity = rand() % 2;
			std::vector<std::wstring> mtempatr = mXmlItems[1];
			for (int i = 0; i < randquantity; i++)
			{
				srand((unsigned)time(NULL));
				int randnumatr = rand() % mtempatr.size();
				auto itrtempatr = mtempatr.begin();
				for (int i = 0; i < randnumatr; i++)
				{
					++itrtempatr;
				}
				randatrb.push_back(*itrtempatr);
				mtempatr.erase(itrtempatr);
			}
			std::map<std::wstring, std::wstring> mBadtempatr = mBadXmlItems[1];
			srand((unsigned)time(NULL));
			int randnum = rand() % mBadtempatr.size();
			auto itrtempatr = mBadtempatr.begin();
			for (int i = 0; i < randnum; i++)
			{
				++itrtempatr;
			}
			randatrb.push_back(itrtempatr->first);
			uml->SetGood(false);
			uml->SetErrorMessage(itrtempatr->second);
			uml->SetAttributes(randatrb);
		}
		//Adding zero to three random operations
		if (!(uml->GetGood()) || randForGood < 40)
		{
			int randquantityOp = rand() % 3;
			std::vector<std::wstring> randOp;
			std::vector<std::wstring> mtempOp = mXmlItems[2];
			for (int i = 0; i < randquantityOp; i++)
			{
				srand((unsigned)time(NULL));
				int randnumOp = rand() % mtempOp.size();
				auto itrtempOp = mtempOp.begin();
				for (int i = 0; i < randnumOp; i++)
				{
					++itrtempOp;
				}
				randOp.push_back(*itrtempOp);
				mtempOp.erase(itrtempOp);
			}
			uml->SetOperations(randOp);
		}
		else
		{
			int randquantityOp = rand() % 2;
			std::vector<std::wstring> randOp;
			std::vector<std::wstring> mtempOp = mXmlItems[2];
			for (int i = 0; i < randquantityOp; i++)
			{
				srand((unsigned)time(NULL));
				int randnumOp = rand() % mtempOp.size();
				auto itrtempOp = mtempOp.begin();
				for (int i = 0; i < randnumOp; i++)
				{
					++itrtempOp;
				}
				randOp.push_back(*itrtempOp);
				mtempOp.erase(itrtempOp);
			}

			std::map<std::wstring, std::wstring> mBadtempOp = mBadXmlItems[2];
			srand((unsigned)time(NULL));
			int randnum = rand() % mBadtempOp.size();
			auto itrtempOp = mBadtempOp.begin();
			for (int i = 0; i < randnum; i++)
			{
				++itrtempOp;
			}
			randOp.push_back(itrtempOp->first);
			uml->SetGood(false);
			uml->SetErrorMessage(itrtempOp->second);
			uml->SetOperations(randOp);

		}
		if ((uml->GetGood()) && randForGood < 20)
		{
			//Inheritance Atributes
			int randquantityInher = rand() % 3;
			std::vector<std::wstring> randatrbIn;
			std::vector<std::wstring> mtempatrIn = mXmlItems[1];
			for (int i = 0; i < randquantityInher; i++)
			{
				srand((unsigned)time(NULL));
				int randnumatrIn = rand() % mtempatrIn.size()-1;
				auto itrtempatrIn = mtempatrIn.begin();
				for (int i = 1; i < randnumatrIn; i++)
				{
					++itrtempatrIn;
				}
				randatrbIn.push_back(*itrtempatrIn);
				mtempatrIn.erase(itrtempatrIn);
			}
			uml->SetInheritanceAttributes(randatrbIn);
			//Inheritance Operations
			int randquantityOpIn = rand() % 3;
			std::vector<std::wstring> randOpIn;
			std::vector<std::wstring> mtempOpIn = mXmlItems[2];
			for (int i = 0; i < randquantityOpIn; i++)
			{
				srand((unsigned)time(NULL));
				int randnumOpIn = rand() % mtempOpIn.size()-1;
				auto itrtempOpIn = mtempOpIn.begin();
				for (int i = 1; i < randnumOpIn; i++)
				{
					++itrtempOpIn;
				}
				randOpIn.push_back(*itrtempOpIn);
				mtempOpIn.erase(itrtempOpIn);
			}
			uml->SetInheritanceOperations(randOpIn);
			int randquantityIn = rand() % 10;
			if (randquantityIn > 3)
			{
				srand((unsigned)time(NULL));
				int randnumItIn = rand() % mInheritance.size();
				auto itrtempIn = mInheritance.begin();
				for (int i = 0; i < randnumItIn; i++)
				{
					++itrtempIn;
				}
				uml->SetNameText(itrtempIn->GetDerived());
				uml->SetInheritance(itrtempIn->GetBase());
				uml->SetHasInheritance(true);
			}
		}
		else if(uml->GetGood())
		{
			//Inheritance
			int randnumItIn = rand() % mBadInheritance.size();
			auto itrtempIn = mBadInheritance.begin();
			for (int i = 0; i < randnumItIn; i++)
			{
				++itrtempIn;
			}
			if (itrtempIn->GetDirection() != L"") 
			{
				uml->SetArrow(false);
			}
			//Inheritance Atributes
			int randquantityIn = rand() % 3;
			std::vector<std::wstring> randatrbIn;
			std::vector<std::wstring> mtempatrIn = mXmlItems[1];
			for (int i = 0; i < randquantityIn; i++)
			{
				srand((unsigned)time(NULL));
				int randnumatrIn = rand() % mtempatrIn.size();
				auto itrtempatrIn = mtempatrIn.begin();
				for (int i = 0; i < randnumatrIn; i++)
				{
					++itrtempatrIn;
				}
				randatrbIn.push_back(*itrtempatrIn);
				mtempatrIn.erase(itrtempatrIn);
			}
			uml->SetInheritanceAttributes(randatrbIn);
			//Inheritance Operations
			int randquantityOpIn = rand() % 3;
			std::vector<std::wstring> randOpIn;
			std::vector<std::wstring> mtempOpIn = mXmlItems[2];
			for (int i = 0; i < randquantityOpIn; i++)
			{
				srand((unsigned)time(NULL));
				int randnumOpIn = rand() % mtempOpIn.size();
				auto itrtempOpIn = mtempOpIn.begin();
				for (int i = 0; i < randnumOpIn; i++)
				{
					++itrtempOpIn;
				}
				randOpIn.push_back(*itrtempOpIn);
				mtempOpIn.erase(itrtempOpIn);
			}
			uml->SetInheritanceOperations(randOpIn);

			uml->SetNameText(itrtempIn->GetDerived());
			uml->SetInheritance(itrtempIn->GetBase());
			uml->SetHasInheritance(true);
			uml->SetGood(false);
			uml->SetErrorMessage(itrtempIn->GetError());
		}
		//Putting the names into uml
		uml->SetLocation(uml->GetX(), uml->GetY());
		game->Add(uml);
	}
}