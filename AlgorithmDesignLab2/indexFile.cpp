#include "indexFile.h"

#include <fstream>

#include "databaseConfiguration.h"

void indexFile::create()
{
	std::ofstream indexFile(databaseConfiguration::indexFileName, std::ios::trunc);
	for(int blockNumber=0;blockNumber<databaseConfiguration::blocksNumber;blockNumber++)
	{
		indexFile<<blockNumber<<','<<(databaseConfiguration::keyMaxValue-databaseConfiguration::keyMinValue)/databaseConfiguration::blocksNumber*blockNumber<<'\n';
	}
	indexFile.close();
}

int indexFile::getNumberOfFittingBlock(int key)
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
