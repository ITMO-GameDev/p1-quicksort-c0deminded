// Qsort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Qsort.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <gtest/gtest.h>

TEST(PivotTest, WrongPivot)
{
	const int length = 9;
	int testArray[length] = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	int expectedArray[length] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	auto comp = [](int a, int b) { return a < b; };

	int pivot = median(testArray, testArray + length - 1, comp);
	EXPECT_EQ(4, pivot);
}

TEST(EmptyArrayTest,EmptyArrayError)
{
	const int length = 1;
	int testArray[length] = {};
	int expectedArray[length] = {};
	auto comp = [](int a, int b) { return a < b; };

	sort(testArray, testArray + length - 1, comp);
	for (int i = 0; i < length; i++)
	{
		EXPECT_EQ(expectedArray[i], testArray[i]);
	}
}
TEST(SingleElementTest,SingleElementError)
{
	int testArray[] = { 1 };
	auto comp = [](int a, int b) { return a < b; };
	sort(testArray, testArray, comp);
	EXPECT_EQ(1, testArray[0]);
}

TEST(Qsort,WrongSort)
{
	const int length = 150;
	auto comp = [](int a, int b) { return a < b; };
	int testArray[length] = {};
	int expectedArray[length] = {};

	for (int i = 0; i < length; i++) {
		int randInt = rand() % 100;
		testArray[i] = randInt;
		expectedArray[i] = randInt;
	}
	std::sort(expectedArray, expectedArray + length);
	sort(testArray, testArray + length - 1, comp);

	for (int i = 0; i < length; i++)
	{
		EXPECT_EQ(expectedArray[i], testArray[i]);
	}
}

int main(int argc,char* argv[])
{	
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
