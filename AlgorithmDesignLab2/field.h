#pragma once

#include <string>

class field
{
public:
	static void editValue(int key, std::string newValue);
	static void deleteByKey(int key);
	static bool addNew(int key, std::string value);
};