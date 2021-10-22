#pragma once
#include <string>
#include <vector>

class block
{
public:
	static std::vector<std::pair<int, std::string>> read(int blockNumber);
	static void print(int blockNumber);
	static void write(int blockNumber, std::vector<std::pair<int, std::string>>& fields);
	static void sortByKey(std::vector<std::pair<int, std::string>>& fields);
};
