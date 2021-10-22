#include "overflowArea.h"

#include <iostream>

#include "block.h"
#include "databaseConfiguration.h"

std::vector<std::pair<int, std::string>> overflowArea::read()
{
	std::vector<std::pair<int, std::string>> fields;
	std::ifstream dataFile(databaseConfiguration::dataFileName, std::ios_base::binary);
	dataFile.seekg(databaseConfiguration::blocksNumber*databaseConfiguration::blockSizeInBytes);
	int key;
	std::string value;
	while(!dataFile.eof())
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

void overflowArea::write(std::vector<std::pair<int, std::string>>& fields)
{
	block::write(databaseConfiguration::blocksNumber, fields);
}

void overflowArea::print()
{
	auto overflowFields = read();
	if(!overflowFields.empty())
		std::cout<<"Overflow area"<< std::endl;
	for (auto overflowField : overflowFields)
	{
		std::cout<<"key: "<<overflowField.first<<" value: "<<overflowField.second<< std::endl;
	}
}
