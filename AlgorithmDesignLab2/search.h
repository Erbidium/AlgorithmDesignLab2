#pragma once
#include <string>
#include <vector>

class search
{
public:
	static int sharrMethod(const std::vector<std::pair<int, std::string>>& fields, int key);
	static int homogeneousBinarySearch(int i, int delta, const std::vector<std::pair<int, std::string>>& fields, int key);
	static bool elementWithKeyExists(const std::vector<std::pair<int, std::string>>& fields, int key);
};
