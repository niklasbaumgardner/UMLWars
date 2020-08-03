/**
 * \file Game.h
 *
 * \author Will Lennon
 *
 * Class that defines the whole game
 */

#pragma once
#include <memory>
#include <vector>
#include "Item.h"
#include "ItemScoreboard.h"
#include "ItemHarold.h"
#include "ItemSharpie.h"
#include "Emitter.h"
#include <map>

/**
 * Class that defines the whole game
 */
class CGame
{
public:
	CGame();

	void Add(std::shared_ptr<CItem> item);
	void Remove(std::shared_ptr<CItem> item);
	void ToBack(std::shared_ptr<CItem> item);
	void OnDraw(Gdiplus::Graphics*, double, double);
	void Update(double);
	void OnMouseMove(double, double);
	void Shoot(double, double);
	void ChangeCharacter(std::wstring);
	//void GenerateUML(double elapsed);

	std::shared_ptr<CItem> HitTest(CItemSharpie*);

	/** Gets the game width
	* \returns Width Game width
	*/
	int GetWidth() { return Width; }

	/** Gets the game height
	* \returns Height Game Height
	*/
	int GetHeight() { return Height; }

	/** Gets mouse x positon
	* \returns Mouse position x
	*/
	double GetMouseX() { return mMouseX; }
	
	/** Gets mouse y position
	* \returns Mouse position y
	*/
	double GetMouseY() { return mMouseY; }

	void Accept(CVisitorItem* visitor);

	/// Game area width in virtual pixels
	const static int Width = 1250;

	/// Game area height in virtual pixels
	const static int Height = 1000;

private:
	/// All of the items to populate our Game
	std::vector<std::shared_ptr<CItem> > mItems;

	/// Scaling to have game work on multiple window sizes
	double mScale; /// scale of the window
	double mXOffset; /// offset in x direction
	double mYOffset; /// offset in y direction

	// Mouse position to draw items at angle
	double mMouseX; /// mouse x position
	double mMouseY; /// mouse y position
	std::wstring mXmlFilename = L"../data/uml.xml"; /// XML file to read and create UML based off

	CEmitter CEmit; /// Emitter creates uml in the game
};

