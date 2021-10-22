#pragma once

#include <string>

class dataFile
{
public:
	static void create();
	static void print();
	static void generate(int numberOfWrittenFieldsInBlock, int numberOfFieldsInOverflowArea);
	static void fitString(std::string& value);
	static std::string randomStringForField();
};

