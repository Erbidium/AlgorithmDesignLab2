#pragma once
#include <string>
#include <vector>

class search
{
public:
	static int sharrMethod(const std::vector<std::pair<int, std::string>>& fields, int key, int& comparisonsNumber);
	static int homogeneousBinarySearch(int key, const std::vector<std::pair<int, std::string>>& fields, int pos, int k, int& comparisonsNumber);
	static bool elementWithKeyExists(const std::vector<std::pair<int, std::string>>& fields, int key, int& comparisonsNumber);
};
