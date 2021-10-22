#include "block.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "databaseConfiguration.h"

std::vector<std::pair<int, std::string>> block::read(int blockNumber)
{
	std::vector<std::pair<int, std::string>> fields;
	std::ifstream dataFile(databaseConfiguration::dataFileName, std::ios_base::binary);
	dataFile.seekg(blockNumber*databaseConfiguration::blockSizeInBytes);
	int key;
	std::string value;
	for(int i=0;i<databaseConfiguration::blockFieldsNumber;i++)
	{
		dataFile.read(reinterpret_cast<char*> (&key), sizeof(key));
		value=std::string(databaseConfiguration::dataFieldNumberSymbols, '\0');
		dataFile.read(value.data(), databaseConfiguration::dataFieldNumberSymbols);
		if(value[0]!='\0')
		{
			fields.emplace_back(std::pair(key, value));
		}
	}
	dataFile.close();
	return fields;
}

void block::print(int blockNumber)
{
	const auto fields = read(blockNumber);
	std::cout<<"Block number: "<<blockNumber<< std::endl;
	for (const auto& field : fields)
	{
		std::cout<<"key: "<<" "<<field.first<<" value: "<<field.second<< std::endl;
	}
}

void block::write(int blockNumber, std::vector<std::pair<int, std::string>>& fields)
{
	std::ofstream dataFile(databaseConfiguration::dataFileName, std::ios_base::binary| std::ios_base::out|std::ios_base::in);
	dataFile.seekp(blockNumber*databaseConfiguration::blockSizeInBytes);
	for (const auto& field : fields)
	{
		int key = field.first;
		std::string value = field.second;
		dataFile.write(reinterpret_cast<char*> (&key), sizeof(key));
		dataFile.write(value.data(), databaseConfiguration::dataFieldNumberSymbols);
	}
	dataFile.close();
}

void block::sortByKey(std::vector<std::pair<int, std::string>>& fields)
{
	std::ranges::sort(fields, [](auto	pair1, auto pair2)->bool
	{
		return pair1.first<pair2.first;
	});

}