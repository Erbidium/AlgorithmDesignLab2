#include "dataFile.h"

#include "databaseConfiguration.h"
#include "overflowArea.h"

#include <iostream>
#include <fstream>

void dataFile::create()
{
	std::ofstream dataFile(databaseConfiguration::dataFileName, std::ios_base::trunc|std::ios_base::binary);
	const std::string nullStr(databaseConfiguration::blockSizeInBytes*databaseConfiguration::blocksNumber, '\0');
	dataFile.write(nullStr.data(), nullStr.size());
	dataFile.close();
}

void dataFile::print()
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
		auto overflowFields = overflowArea::read();
		if(!overflowFields.empty())
			std::cout<<"Overflow area"<< std::endl;
		for (auto overflowField : overflowFields)
		{
			std::cout<<"key: "<<key<<" value: "<<value<< std::endl;
		}
	}
	dataFile.close();
}

void dataFile::generate(int numberOfWrittenFieldsInBlock, int numberOfFieldsInOverflowArea)
{
	if(numberOfWrittenFieldsInBlock>databaseConfiguration::blockFieldsNumber)
	{
		numberOfWrittenFieldsInBlock=databaseConfiguration::blockFieldsNumber;
	}
	std::ofstream dataFile(databaseConfiguration::dataFileName, std::ios_base::binary);
	int key;
	std::string value;
	for(int i=0;i<databaseConfiguration::blocksNumber;i++)
	{
		dataFile.seekp(i*databaseConfiguration::blockSizeInBytes);
		for(int j=0;j<numberOfWrittenFieldsInBlock;j++)
		{
			key = databaseConfiguration::blockFieldsNumber*i+j;
			value=std::string(databaseConfiguration::dataFieldNumberSymbols, '\0');
			std::string newValue = randomStringForField();
			value.replace(0, value.size(), newValue);
			dataFile.write(reinterpret_cast<char*> (&key), sizeof(key));
			dataFile.write(value.data(), databaseConfiguration::dataFieldNumberSymbols);
		}
	}
	dataFile.close();
	int currentKeyInOverflow=databaseConfiguration::keyMaxValue + 5 + rand()%20;
	std::vector<std::pair<int, std::string>> fields(numberOfFieldsInOverflowArea);
	for(int i=0;i<numberOfFieldsInOverflowArea;i++)
	{
		fields[i].first=currentKeyInOverflow;
		value = randomStringForField();
		fields[i].second=value;
		currentKeyInOverflow+=2+rand()%7;
	}
	//overflowArea::write(fields);
}

void dataFile::fitString(std::string& value)
{
	if(value.size()>databaseConfiguration::dataFieldNumberSymbols)
	{
		value=value.substr(0, databaseConfiguration::dataFieldNumberSymbols);
	}
	else
	{
		value=value+ std::string(databaseConfiguration::dataFieldNumberSymbols-value.size(), '\0');
	}
}

std::string dataFile::randomStringForField()
{
	int length=rand()%10+rand()%(databaseConfiguration::dataFieldNumberSymbols-10);
	std::string value(databaseConfiguration::dataFieldNumberSymbols, '\0');
	for(int i=0;i<length;i++)
	{
		value[i]=char(97+rand()%(122-97));
	}
	fitString(value);
	return value;
}
