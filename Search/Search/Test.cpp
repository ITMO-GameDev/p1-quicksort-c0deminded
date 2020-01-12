// Search.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <gtest/gtest.h>
#include "Dictionary.h"

TEST(SearchTest,InitTest)
{
	Dictionary<int, std::string> tmp;
	EXPECT_EQ(0, tmp.size());
}

TEST(SearchTest, InputTest)
{
	Dictionary<int, std::string> tmp;
	for (auto i = 0; i < 10; i++)
	{
		tmp.put(i, "SomeValue");
	}
	EXPECT_EQ(10, tmp.size());
}

TEST(SearchTest, ContainsTest)
{
	Dictionary<int, std::string> tmp;
	for (auto i = 0; i < 10; i++)
	{
		tmp.put(i, std::to_string(i));
		EXPECT_TRUE(tmp.contains(i));
	}
	EXPECT_EQ(10, tmp.size());
	EXPECT_FALSE(tmp.contains(15));
}

TEST(SearchTest, RemoveTest)
{
	Dictionary<int, std::string> tmp;
	for (auto i = 0; i < 10; i++)
	{
		tmp.put(i, "SomeValue");
	}
	for (auto i = 0; i < 5; i++)
	{
		tmp.remove(i);
	}

	for (auto i = 0; i < 10; i++)
	{
		if (i < 5)
			EXPECT_FALSE(tmp.contains(i));
		else
			EXPECT_TRUE(tmp.contains(i));
	}
	EXPECT_EQ(5, tmp.size());
}



TEST(SearchTest, StrKeyTest)
{
	Dictionary<std::string, int> tmp;
	for (auto i = 0; i < 10; i++)
	{
		tmp[std::to_string(i)] = i;
	}
	for (auto i = 0; i < 10; i++)
	{
		EXPECT_TRUE(tmp.contains(std::to_string(i)));
		EXPECT_TRUE(tmp[std::to_string(i)] == i);
	}
}


TEST(SearchTest, IteratorForwardTest)
{
	Dictionary<std::string, int> tmp;
	auto k = 1;
	for (auto i = 0; i < 10; i++)
	{
		tmp[std::to_string(i)] = i;
	}
	for (auto it = tmp.iterator(); it.hasNext(); it.next())
	{
		EXPECT_TRUE(tmp[it.key()] == it.get());
		k++;
	}
	EXPECT_EQ(k, tmp.size());
}

TEST(SearchTest, IteratorSetTest)
{
	Dictionary<std::string, int> tmp;
	for (auto i = 0; i < 30; i++)
	{
		tmp[std::to_string(i)] = i;
	}
	auto it = tmp.iterator();
	for (it; it.hasNext(); it.next())
	{
		it.set(16);
	}
	it.set(16);
	for (auto i = 0; i < 30; i++)
	{
		EXPECT_EQ(16, tmp[std::to_string(i)]);
	}
}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


