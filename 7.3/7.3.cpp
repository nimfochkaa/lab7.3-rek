#include "pch.h"
#include "CppUnitTest.h"
#include "../7.3 рек/7.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace My73
{
	TEST_CLASS(My73)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const int colCount = 5;
            int row[] = { -3, 4, -1, 2, 5 };
            int* a[] = { row };

            bool hasNegative = false;
            int sum = CalculateSumOfRow(a, 0, colCount, 0, 0, hasNegative);

            Assert::IsTrue(hasNegative, L"Should detect a negative value in the row");
            Assert::AreEqual(7, sum, L"Sum of row with negatives is incorrect");
        }

        TEST_METHOD(TestCalculateSum)
        {
            const int rowCount = 3;
            const int colCount = 3;
            int row1[] = { 1, -2, 3 };
            int row2[] = { 4, 5, 6 };
            int row3[] = { -7, 8, -9 };

            int* a[] = { row1, row2, row3 };

            int totalSum = CalculateSum(a, rowCount, colCount, 0, 0);

            Assert::AreEqual(-6, totalSum, L"Total sum of rows with at least one negative element is incorrect");
   
		}
	};
}
