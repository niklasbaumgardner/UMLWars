#include "pch.h"
#include "Game.h"
#include "ItemScoreboard.h"
#include "ItemHarold.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CGameTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(FirstTest)
		{
			CGame game;
			// This is an empty test just to ensure the system is working
		}

	};
}