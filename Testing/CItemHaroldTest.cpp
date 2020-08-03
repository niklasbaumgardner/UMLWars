#include "pch.h"
#include "Item.h"
#include "Game.h"
#include "ItemHarold.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	/** Mock class for testing CItem */
	class CItemHaroldMock : public CItemHarold
	{
	public:
		CItemHaroldMock(CGame* game) : CItemHarold(game) {}
	};
	TEST_CLASS(TestItemHarold)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestNothing)
		{
			CGame game;
			CItemHaroldMock ItemHarold(&game);
		}

	};
}