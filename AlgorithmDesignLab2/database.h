#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "databaseConfiguration.h"

class database
{
public:
	static void createIndexFile()
	{
		std::ofstream indexFile(databaseConfiguration::indexFileName, std::ios::trunc);
		for(int blockNumber=0;blockNumber<databaseConfiguration::blocksNumber;blockNumber++)
		{
			indexFile<<blockNumber<<','<<(databaseConfiguration::keyMaxValue-databaseConfiguration::keyMinValue)/databaseConfiguration::fieldsNumber*(blockNumber)<<'\n';
		}
		indexFile.close();
	}
	static void createDataFile()
	{
		std::ofstream dataFile(databaseConfiguration::dataFileName, std::ios_base::trunc|std::ios_base::binary);
		const std::string nullStr(databaseConfiguration::blockSizeInBytes*databaseConfiguration::blocksNumber, '\0');
		dataFile.write(nullStr.data(), nullStr.size());
		dataFile.close();
	}

	static auto readBlock(int blockNumber)
	{
		std::vector<std::pair<int, std::string>> fields;
		std::ifstream dataFile(databaseConfiguration::dataFileName, std::ios_base::binary);
		dataFile.seekg(blockNumber*databaseConfiguration::blockSizeInBytes);
		int key;
		std::string value(databaseConfiguration::dataFieldNumberSymbols, '\0');
		for(int i=0;i<databaseConfiguration::fieldsNumber;i++)
		{
			dataFile.read(reinterpret_cast<char*> (&key), sizeof(key));
			dataFile.read(value.data(), databaseConfiguration::dataFieldNumberSymbols);
			if(value[0]!='\0')
			{
				fields.emplace_back(std::pair(key, value));
			}
		}
		dataFile.close();
		return fields;
	}
	static void writeBlock(int blockNumber, const static std::vector<std::pair<int, std::string>>& fields)
	{
		std::ofstream dataFile(databaseConfiguration::dataFileName, std::ios_base::binary);
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
	static int getNumberOfFittingBlock(int key)
	{
		std::ifstream indexFile(databaseConfiguration::indexFileName);
		for(int i=0;i<databaseConfiguration::blocksNumber;i++)
		{
			std::string blockNumber, startValueInBlock;
			std::getline(indexFile, blockNumber, ',');
			std::getline(indexFile, startValueInBlock, '\n');
			if((key>=std::stoi(startValueInBlock))&&(key<std::stoi(startValueInBlock)+databaseConfiguration::blockFieldsNumber))
			{
				return std::stoi(blockNumber);
			}
		}
		indexFile.close();
		return -1;
	}
	static std::vector<std::pair<int, std::string>> getOverflowArea()
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

	static void sortBlock(std::vector<std::pair<int, std::string>>& fields)
	{
		std::ranges::sort(begin(fields), end(fields), [](auto	pair1, auto pair2)->bool
		{
			return pair1.first<pair2.first;
		});
	}
	static void printDataFile()
	{
		std::ifstream dataFile(databaseConfiguration::dataFileName, std::ios_base::binary);
		int key;
		std::string value;
		for(int i=0;i<databaseConfiguration::blocksNumber;i++)
		{
			std::cout<<"Block number: "<<i<< std::endl;
			dataFile.seekg(i*databaseConfiguration::blockSizeInBytes);
			for(int j=0;j<databaseConfiguration::blockFieldsNumber;j++)
			{
				dataFile.read(reinterpret_cast<char*> (&key), sizeof(key));
				value=std::string(databaseConfiguration::dataFieldNumberSymbols, '\0');
				dataFile.read(value.data(), databaseConfiguration::dataFieldNumberSymbols);

				if(value[0]!='\0')
				{
					std::cout<<"key: "<<j<<" "<<key<<" value: "<<value<< std::endl;
				}
				else
				{
					break;
				}
				
			}
			auto overflowFields = getOverflowArea();
			if(!overflowFields.empty())
				std::cout<<"Overflow area"<< std::endl;
			for (auto overflowField : overflowFields)
			{
				std::cout<<"key: "<<key<<" value: "<<value<< std::endl;
			}
		}
		dataFile.close();
	}

	static void generateDataFile()
	{
		std::ofstream dataFile(databaseConfiguration::dataFileName, std::ios_base::binary|std::ios_base::ate);
		int key;
		std::string value;
		for(int i=0;i<databaseConfiguration::blocksNumber;i++)
		{
			dataFile.seekp(i*databaseConfiguration::blockSizeInBytes);
			for(int j=0;j<50;j++)
			{
				key = databaseConfiguration::blockFieldsNumber*i+j;
				value = std::string(databaseConfiguration::dataFieldNumberSymbols, '\0');
				std::string newValue = "dfhfthxfmnxfjnzfxn";
				value.replace(0, newValue.size(), newValue);
				dataFile.write(reinterpret_cast<char*> (&key), sizeof(key));
				dataFile.write(value.data(), databaseConfiguration::dataFieldNumberSymbols);
			}
		}
		dataFile.close();
	}
};

