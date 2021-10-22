#pragma once

#include <string>

class field
{
public:
	static bool editValue(int key, std::string newValue, int& comparisonsNumber);
	static bool deleteByKey(int key, int& comparisonsNumber);
	static bool searchByKey(int key, std::string& value, int& comparisonsNumber);
	static bool addNew(int key, std::string value, int& comparisonsNumber);
};