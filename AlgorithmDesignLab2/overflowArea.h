#pragma once
#include <vector>
#include <fstream>

class overflowArea
{
public:
	static std::vector<std::pair<int, std::string>> read();
	static void write(std::vector<std::pair<int, std::string>>& fields);
	static void print();
};
