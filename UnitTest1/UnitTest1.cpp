#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3/Dijkstra’s_algorithm.h"
#include "../lab3/list.h"
#include "../lab3/string.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
		String file_1 = "test_1.txt";
		String file_2 = "test_2.txt";
	public:
		TEST_METHOD(Test_1)
		{
			Dijkstra_algorithm board;
			board.read_from_files(file_1);
			int cost = 48;
			Assert::AreEqual(cost, board.algorithm(1, 3));
		}
		TEST_METHOD(Test_2)
		{
			Dijkstra_algorithm board;
			board.read_from_files(file_1);
			int cost = 85;
			Assert::AreEqual(cost, board.algorithm(4, 1));
		}
		TEST_METHOD(Test_3)
		{
			Dijkstra_algorithm board_2;
			board_2.read_from_files(file_2);
			int cost = 40;
			Assert::AreEqual(cost, board_2.algorithm(4, 1));
		}
		TEST_METHOD(Test_4)
		{
			Dijkstra_algorithm board_2;
			board_2.read_from_files(file_2);
			int cost = 29;
			Assert::AreEqual(cost, board_2.algorithm(3, 2));
		}
	};
}
