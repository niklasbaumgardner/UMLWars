/**
* \file Game.cpp
*
* \author Will Lennon
*/

#include "pch.h"
#include "Game.h"
#include "Item.h"
#include "XmlNode.h"
#include "Emitter.h"
#include "VisitorItemUML.h"
#include "VisitorItemUMLCheck.h"
#include "VisitorItemSharpieShoot.h"
#include "VisitorItemHarold.h"
#include "VisitorItemScoreboard.h"
#include "VisitorItemUMLCheck.h"
#include <memory>
#include <string>
#include <algorithm>

using namespace std;
using namespace Gdiplus;

/** Game constructor
* Adds crucial parts to playing the game
*/
CGame::CGame() 
{
	// reads xml file and returns vector of vectors
	CEmitter emit;
	emit.Load(mXmlFilename);
	emit.ToXmlItems();
	emit.ToBadXmlItems();
	CEmit = emit;

	// Initialize harold at game start
	shared_ptr<CItem> harold = make_shared<CItemHarold>(this);
	harold->SetLocation(0, 900);
	this->Add(harold);

	// Create initial scoreboard
	shared_ptr<CItem> scoreboard = make_shared<CItemScoreboard>(this);
	this->Add(scoreboard);

	// Create and add sharpie being used
	shared_ptr<CItem> sharpie = make_shared<CItemSharpie>(this);
	sharpie->SetLocation(harold->GetX(), harold->GetY());
	this->Add(sharpie);

}

/** Adds an item to the game
* \param item Item being added
*/
void CGame::Add(std::shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/** Removes an item from the game
* \param item Item being removed
*/
void CGame::Remove(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
	}
}

/**
 * Moves an item to the end of mitems list after being moved
 * \param item Item to move to end of list
 */

void CGame::ToBack(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
		mItems.push_back(item);
	}
}

/** Draw the game
* \param graphics The GDI+ graphics context to draw on
* \param wid width
* \param height height
*/
void CGame::OnDraw(Gdiplus::Graphics* graphics, double wid, double height)
{
	// Fill background with black
	SolidBrush brush(Color::White);
	graphics->FillRectangle(&brush, 0, 0, wid, height);

	//
	// Automatic Scaling
	//
	float scaleX = float(wid) / float(Width);
	float scaleY = float(height) / float(Height);
	mScale = min(scaleX, scaleY);

	mXOffset = wid / 2.0f;
	mYOffset = 0;
	if (height > Height * mScale)
	{
		mYOffset = (float)((height - Height * mScale) / 2);
	}

	graphics->TranslateTransform(mXOffset, mYOffset);
	graphics->ScaleTransform(mScale, mScale);

	// Draws all the items
	for(auto item: mItems)
	{
		item->Draw(graphics);
	}

}

/**
* Updates every item of the game
* \param elapsed Elapsed time since window last drawn
*/
void CGame::Update(double elapsed)
{

	CEmit.GenerateUML(elapsed, this);
	
	// Initialize visitors for the 3 constant game items
	CVisitorItemSharpieShoot visitorItemSharpieShoot;
	CVisitorItemHarold visitorItemHarold;
	CVisitorItemScoreboard visitorItemScoreboard;
	
	for (auto item : mItems)
	{
		item->Update(elapsed);
		item->Accept(&visitorItemSharpieShoot);
		item->Accept(&visitorItemHarold);
		item->Accept(&visitorItemScoreboard);
	}

	// Gets the sharpie object to be passed to hit test
	CItemSharpie* sharpie = visitorItemSharpieShoot.GetSharpItem();

	// Check if any uml pointers hit
	auto hit = HitTest(sharpie);
	if (hit != nullptr)
	{
		// Visit the uml object being hit
		CVisitorItemUMLCheck uml;
		hit->Accept(&uml);
		
		// Checks if uml was hit or left the screen without being hit
		if (uml.IsHit())
		{
			// Update score accordingly
			if ((hit)->GetGood())
			{
				visitorItemScoreboard.AddUnfair();
			}
			else
			{
				visitorItemScoreboard.AddCorrect();
			}
		}
		else if (uml.IsMissed())
		{
			
			if (!uml.GetGood())
			{
				visitorItemScoreboard.AddMissed();
			}
			Remove(hit);
		}
		// Resets sharpie after collision
		sharpie->Reset(visitorItemHarold.GetX(), visitorItemHarold.GetY());
	}

	if (visitorItemSharpieShoot.GetX() > Width/2||visitorItemSharpieShoot.GetX()< -Width/2)
	{
		sharpie->ReverseVelocity();
		// Reverse sharpie movement on window edge hit
	}
	if(visitorItemSharpieShoot.GetY()<0)
	{
		sharpie->Reset(visitorItemHarold.GetX(), visitorItemHarold.GetY());
	}
	if (visitorItemSharpieShoot.GetY() > Height)
	{
		sharpie->Reset(visitorItemHarold.GetX(), visitorItemHarold.GetY());
	}
	// Reset sharpie if leaves screen
}

/**
* Tracks mouse movement to angle items
* \param x X position of mouse
* \param y Y position of mouse
*/
void CGame::OnMouseMove(double x, double y)
{
	mMouseX = (x - mXOffset) / mScale;
	mMouseY = (y - mYOffset) / mScale;
}

/**
* Accepts a visitor into the game
* \param visitor Ref to visitor that is accepted
*/
void CGame::Accept(CVisitorItem* visitor)
{
	for (auto item : mItems)
	{
		item->Accept(visitor);
	}


}

/** Shoots the sharpie object associatad with the game
* \param x X position of the mouse
* \param y Y position of the mouse when clicked
*/
void CGame::Shoot(double x, double y)
{
	CVisitorItemSharpieShoot visitor;
	this->Accept(&visitor);
	visitor.Shoot(x, y);
}


/** 
* Changes the character image in the game
* 
*/
void CGame::ChangeCharacter(wstring character) 
{
	CVisitorItemHarold visitor;
	this->Accept(&visitor);
	visitor.SetCharacter(character);
}

/**
* Determines if a uml item is hit by the sharpie
* \param sharpie The game sharpie that has been shot
* \returns UML item belonging to the game that was hit
*/
std::shared_ptr<CItem> CGame::HitTest(CItemSharpie* sharpie)
{
	// Initialize a visitor to uml objects
	CVisitorItemUMLCheck uml;
	for (auto item: mItems)
	{
		// Tries to visit all items in the game
		item->Accept(&uml);

		if (uml.IsUML())
		{
			uml.Reset();
			// If the uml hasnt been hit already see if its about to be
			if (!uml.IsHit())
			{
				// 
				if (sharpie->HitTest((item)))
				{
					uml.SetHit();
					return item;
				}
				
				if (uml.GetY() + uml.Height() / 2 > Height)
				{
					uml.SetMissed();
					return item;
				}
				// Return the item if it leaves the screen or is hit by the sharpie
				
			}
			else if (uml.IsHit() && uml.GetTimer() <= 0)
			{
				// Removes an item that has been hit and needs to be removed
				Remove(item);
				return nullptr;
			}
		}
	}
	
	return nullptr;
	
}