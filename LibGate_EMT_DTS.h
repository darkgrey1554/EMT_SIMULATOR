#pragma once
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include <windows.h>
#include <vector>
#include <iostream>


enum class TypeData
{
	EMPTY,
	ANALOG,
	DISCRETE,
	BINAR,
	GROUP
};

enum class TypeSignal
{
	EMPTY,
	OUTPUT,
	INPUT
};

std::ostream& operator<<(std::ostream& out, TypeSignal& m);
std::ostream& operator<<(std::ostream& out, TypeData& m);

struct InfoSharedMemory
{
	std::string namememory;
	TypeSignal type_signal = TypeSignal::EMPTY;
	TypeData type_data = TypeData::EMPTY;
	int size_data = 0;
	HANDLE mutex = INVALID_HANDLE_VALUE;
	HANDLE semaphor = INVALID_HANDLE_VALUE;
	HANDLE memory = INVALID_HANDLE_VALUE;
	void* buffer= NULL;
	int k = 0;
	void clear()
	{
		namememory.clear();
	    type_signal = TypeSignal::EMPTY;
		type_data = TypeData::EMPTY;
		size_data = 0;
		mutex = INVALID_HANDLE_VALUE;
		semaphor = INVALID_HANDLE_VALUE;
		memory = INVALID_HANDLE_VALUE;
		buffer = NULL;
	}
};

class Gate_EMT_DTS
{
	std::vector<InfoSharedMemory> infovector;

	int WriteData(void* buf, TypeData td, int size = NULL, int index = NULL, int grtype = NULL);
	int ReadData(void* buf, TypeData td, int* size = NULL, int* index = NULL, int* grtype = NULL);
	int ReadConfigFile(const char* filename);

public:

	Gate_EMT_DTS();
	~Gate_EMT_DTS();
	
	int Init(const char* filename);
	
	int ReadAnalogData(void* buf);
	int ReadDiscreteData(void* buf);
	int ReadBinarData(void* buf);
	int ReadGroupData(void* buf, int* size, int* index, int* grtype);

	int WriteAnalogData(void* buf);
	int WriteDiscreteData(void* buf);
	int WriteBinarData(void* buf);
	int WriteGroupData(void* buf, int size, int index, int grtype);

};