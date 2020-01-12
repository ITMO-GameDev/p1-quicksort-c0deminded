// MemoryManagement.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <gtest/gtest.h>
#include "MemoryAllocator.h"

TEST(MemManagement, GeneralTest) 
{
	MemoryAllocator allocator;
	allocator.init();
	int* pi = (int*)allocator.alloc(1000 * sizeof(int));
	double* pd = (double*)allocator.alloc(200 * sizeof(double));
	int* pa = (int*)allocator.alloc(50 * sizeof(int));
	allocator.free(pi);
	allocator.free(pd);
	allocator.free(pa);
	allocator.destroy();
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
