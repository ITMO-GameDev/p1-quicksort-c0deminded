#pragma once
#include <cstddef>
#include <list>
#include "StackedList.cpp"
#include <vector>
#include <set>
#include <string>
#include <iostream>


class FSA
{
protected:
    std::size_t m_chunkSize;
    std::vector<void*> pages;
    std::set<void*> dumpSet;
    const static size_t pageSize = 4096;
    bool isInit;
	
    struct  FreeHeader {
    };
    using Node = StackedList<FreeHeader>::Node;
	StackedList<FreeHeader> m_freeList;

    void* m_start_ptr = nullptr;

    virtual void* request_page();
    virtual  void chunk_page(void* page);
	
public:
    FSA(std::size_t chunkSize);
    virtual ~FSA();
    virtual void init();
    virtual void* alloc();
    virtual bool free(void* ptr);
    virtual void destroy();
    virtual void dumpBlocks();
};

