// Сontainers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Array.h"
#include <iostream>
#include <gtest/gtest.h>

TEST(ContainersTest,InitTest)
{
	Array<int> testArr;
	EXPECT_EQ(0, testArr.size());
	EXPECT_EQ(8, testArr.capacity());
}

TEST(ContainersTest,InitSizeTest)
{
	Array<int> testArr(20);
	EXPECT_EQ(0, testArr.size());
	EXPECT_EQ(20, testArr.capacity());
}

TEST(ContainersTest,EmptyInsertTest)
{
	Array<int> testArr;
	testArr.insert(2);
	EXPECT_EQ(2, testArr[0]);
	testArr.insert(5);
	EXPECT_EQ(5, testArr[1]);
	EXPECT_EQ(2, testArr.size());
}

TEST(ContainersTest,FullInsertTest)
{
	Array<int> testArr(1);
	testArr.insert(2);
	EXPECT_EQ(2, testArr[0]);
	testArr.insert(5);
	EXPECT_EQ(5, testArr[1]);

	EXPECT_EQ(2, testArr.size());
}

TEST(ContainersTest,EmptyPlaceInsertTest)
{
	Array<int> testArr(3);
	testArr.insert(2);
	EXPECT_EQ(2, testArr[0]);
	testArr.insert(1, 5);
	EXPECT_EQ(5, testArr[1]);
	EXPECT_EQ(2, testArr.size());
}

TEST(ContainersTest,NoPlaceInsertTest)
{
	Array<int> testArr(3);
	testArr.insert(2);
	EXPECT_EQ(2, testArr[0]);
	testArr.insert(5);
	EXPECT_EQ(5, testArr[1]);
	testArr.insert(1, 10);
	EXPECT_EQ(10, testArr[1]);
	EXPECT_EQ(5, testArr[2]);
	EXPECT_EQ(3, testArr.size());
}

TEST(ContainersTest,FullArrayInsertInPlaceTest)
{
	Array<int> testArr(2);
	testArr.insert(2);
	EXPECT_EQ(2, testArr[0]);
	testArr.insert(5);
	EXPECT_EQ(5, testArr[1]);
	testArr.insert(1, 10);
	EXPECT_EQ(10, testArr[1]);
	EXPECT_EQ(5, testArr[2]);
	EXPECT_EQ(3, testArr.size());
}

TEST(ContainersTest,RemoveLastTest)
{
	Array<int> testArr(2);
	testArr.insert(2);
	testArr.insert(5);
	EXPECT_EQ(2, testArr.size());
	testArr.remove(1);
	EXPECT_EQ(1, testArr.size());
}

TEST(ContainersTest,RemoveMiddle)
{
	Array<int> testArr(2);
	testArr.insert(2);
	EXPECT_EQ(2, testArr[0]);
	testArr.insert(5);
	EXPECT_EQ(5, testArr[1]);
	testArr.insert(10);
	EXPECT_EQ(10, testArr[2]);
	testArr.remove(1);
	EXPECT_EQ(2, testArr.size());
	EXPECT_EQ(10, testArr[1]);
}


TEST(ContainersTest,IteratorInitTest)
{
	Array<int> testArr;
	for (int i = 0; i < 3; ++i)
		testArr.insert(i);
	auto it = testArr.iterator();

	EXPECT_EQ(0, it.get());
	EXPECT_FALSE(it.hasPrev());
}

TEST(ContainersTest,IteratorNextEmptyTest)
{
	Array<int> testArr;
	testArr.insert(2);
	auto it = testArr.iterator();
	EXPECT_FALSE(it.hasNext());
}

TEST(ContainersTest,IteratorPrevEmptyTest)
{
	Array<int> testArr;
	testArr.insert(2);
	auto it = testArr.iterator();
	EXPECT_FALSE(it.hasPrev());
}

TEST(ContainersTest,IteratorNextTest)
{
	Array<int> testArr;
	testArr.insert(2);
	testArr.insert(5);
	auto it = testArr.iterator();
	EXPECT_TRUE(it.hasNext());
}

TEST(ContainersTest,IteratorPrevTest)
{
	Array<int> testArr;
	testArr.insert(2);
	testArr.insert(5);
	auto it = testArr.iterator();
	it.next();
	EXPECT_TRUE(it.hasPrev());
}

TEST(ContainersTest,IteratorTooFarTest)
{
	Array<int> testArr;
	testArr.insert(2);
	testArr.insert(5);
	auto it = testArr.iterator();
	it.next();
	it.next();
	EXPECT_EQ(5, it.get());
}

TEST(ContainersTest,IteratorTooFarBackTest)
{
	Array<int> testArr;
	testArr.insert(2);
	testArr.insert(5);
	auto it = testArr.iterator();
	it.next();
	it.prev();
	it.prev();
	EXPECT_EQ(2, it.get());
}

TEST(ContainersTest,IteratorMoveToIndexTest)
{
	Array<int> testArr;
	for (int i = 0; i < 3; ++i)
		testArr.insert(i);
	auto it = testArr.iterator();
	it.toIndex(1);
	EXPECT_EQ(1, it.get());
	it.next();
	EXPECT_EQ(2, it.get());
	EXPECT_FALSE(it.hasNext());
}

TEST(ContainersTest,IteratorInsertTest)
{
	Array<int> testArr;
	for (int i = 0; i < 2; ++i)
		testArr.insert(i);
	auto it = testArr.iterator();
	it.insert(10);
	EXPECT_EQ(10, it.get());
	EXPECT_EQ(3, testArr.size());
}

TEST(ContainersTest,IteratorRemoveTest)
{
	Array<int> testArr;
	for (int i = 0; i < 2; ++i)
		testArr.insert(i);
	auto it = testArr.iterator();
	it.remove();
	EXPECT_EQ(1, it.get());
	EXPECT_EQ(1, testArr.size());
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}