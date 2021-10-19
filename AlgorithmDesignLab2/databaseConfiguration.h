#pragma once
#include <string>

class databaseConfiguration
{
public:
	inline static constexpr int fieldsNumber = 10000;
	inline static constexpr int blockFieldsNumber = 250;
	inline static constexpr int blocksNumber = fieldsNumber/blockFieldsNumber;
	inline static constexpr int dataFieldNumberSymbols = 80;
	inline static constexpr int blockSizeInBytes = (dataFieldNumberSymbols*sizeof(char)+sizeof(int))*blockFieldsNumber;
	inline static constexpr int keyMaxValue = blocksNumber;
	inline static constexpr int keyMinValue = 0;
	inline static std::string indexFileName = "index.txt";
	inline static std::string dataFileName = "data.txt";
};

