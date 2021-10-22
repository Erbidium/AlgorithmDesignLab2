#include "dataFile.h"

#include "databaseConfiguration.h"
#include "overflowArea.h"
#include "block.h"

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
	for(int i=0;i<databaseConfiguration::blocksNumber;i++)
	{
		block::print(i);
	}
	overflowArea::print();
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
			value = randomStringForField();
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
	overflowArea::write(fields);
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
