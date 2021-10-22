#include "field.h"

#include <iostream>

#include "block.h"
#include "databaseConfiguration.h"
#include "dataFile.h"
#include "indexFile.h"
#include "overflowArea.h"
#include "search.h"

bool field::editValue(int key, std::string newValue, int& comparisonsNumber)
{
	dataFile::fitString(newValue);
	const int blockNumber = indexFile::getNumberOfFittingBlock(key);
	if(blockNumber>=0)
	{
		auto blockFields = block::read(blockNumber);
		const int indexInBlock = search::sharrMethod(blockFields, key, comparisonsNumber);
		if(indexInBlock>=0)
		{
			blockFields[indexInBlock].second=newValue;
			block::write(blockNumber, blockFields);
			return true;
		}
		return false;
	}
	auto overflowAreaFields = overflowArea::read();
	std::cout<<overflowAreaFields.size()<< std::endl;
	const int indexInOverflowArea = search::sharrMethod(overflowAreaFields, key, comparisonsNumber);
	if(indexInOverflowArea>=0)
	{
		overflowAreaFields[indexInOverflowArea].second=newValue;
		overflowArea::write(overflowAreaFields);
		return true;
	}
	return false;
}

bool field::deleteByKey(int key, int& comparisonsNumber)
{
	const int blockNumber = indexFile::getNumberOfFittingBlock(key);
	if(blockNumber>=0)
	{
		auto blockFields = block::read(blockNumber);
		const int indexInBlock = search::sharrMethod(blockFields, key, comparisonsNumber);
		if(indexInBlock>=0)
		{
			blockFields.erase(blockFields.begin()+indexInBlock);
			blockFields.emplace_back(0, std::string(databaseConfiguration::dataFieldNumberSymbols, '\0'));
			block::write(blockNumber, blockFields);
			return true;
		}
		return false;
	}
	auto overflowAreaFields = overflowArea::read();
	const int indexInOverflowArea = search::sharrMethod(overflowAreaFields, key, comparisonsNumber);
	if(indexInOverflowArea>=0)
	{
		overflowAreaFields.erase(overflowAreaFields.begin()+ indexInOverflowArea);
		overflowAreaFields.emplace_back(0, std::string(databaseConfiguration::dataFieldNumberSymbols, '\0'));
		overflowArea::write(overflowAreaFields);
		return true;
	}
	return false;
}

bool field::searchByKey(int key, std::string& value, int& comparisonsNumber)
{
	const int blockNumber = indexFile::getNumberOfFittingBlock(key);
	if(blockNumber>=0)
	{
		auto blockFields = block::read(blockNumber);
		const int indexInBlock = search::sharrMethod(blockFields, key, comparisonsNumber);
		if(indexInBlock>=0)
		{
			value = blockFields[indexInBlock].second;
			return true;
		}
		return false;
	}
	auto overflowAreaFields = overflowArea::read();
	const int indexInOverflowArea = search::sharrMethod(overflowAreaFields, key, comparisonsNumber);
	if(indexInOverflowArea>=0)
	{
		value = overflowAreaFields[indexInOverflowArea].second;
		return true;
	}
	return false;
}

bool field::addNew(int key, std::string value, int& comparisonsNumber)
{
	dataFile::fitString(value);
	const int blockNumber = indexFile::getNumberOfFittingBlock(key);
	if(blockNumber>=0)
	{
		auto blockFields = block::read(blockNumber);
		if(search::elementWithKeyExists(blockFields, key, comparisonsNumber))
		{
			return false;
		}
		blockFields.emplace_back(key, value);
		block::sortByKey(blockFields);
		block::write(blockNumber, blockFields);
	}
	else
	{
		auto overflowAreaFields = overflowArea::read();
		if(search::elementWithKeyExists(overflowAreaFields, key, comparisonsNumber))
		{
			return false;
		}
		overflowAreaFields.emplace_back(key, value);
		block::sortByKey(overflowAreaFields);
		overflowArea::write(overflowAreaFields);
	}
	return true;
}
