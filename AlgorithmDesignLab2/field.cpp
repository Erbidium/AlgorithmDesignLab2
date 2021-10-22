#include "field.h"

#include "block.h"
#include "databaseConfiguration.h"
#include "dataFile.h"
#include "indexFile.h"
#include "overflowArea.h"
#include "search.h"

void field::editValue(int key, std::string newValue)
{
	dataFile::fitString(newValue);
	const int blockNumber = indexFile::getNumberOfFittingBlock(key);
	auto blockFields = block::read(blockNumber);
	const int indexInBlock = search::sharrMethod(blockFields, key);
	if(indexInBlock>=0)
	{
		blockFields[indexInBlock].second=newValue;
		block::write(blockNumber, blockFields);
	}
	else
	{
		auto overflowAreaFields = overflowArea::read();
		const int indexInOverflowArea = search::sharrMethod(overflowAreaFields, key);
		overflowAreaFields[indexInOverflowArea].second=newValue;
		overflowArea::write(overflowAreaFields);
	}
}

void field::deleteByKey(int key)
{
	const int blockNumber = indexFile::getNumberOfFittingBlock(key);
	auto blockFields = block::read(blockNumber);
	const int indexInBlock = search::sharrMethod(blockFields, key);
	if(indexInBlock>=0)
	{
		blockFields.erase(blockFields.begin()+indexInBlock);
		block::write(blockNumber, blockFields);
	}
	else
	{
		auto overflowAreaFields = overflowArea::read();
		const int indexInOverflowArea = search::sharrMethod(overflowAreaFields, key);
		overflowAreaFields.erase(overflowAreaFields.begin()+ indexInOverflowArea);
		overflowArea::write(overflowAreaFields);
	}
}

bool field::addNew(int key, std::string value)
{
	dataFile::fitString(value);
	const int blockNumber = indexFile::getNumberOfFittingBlock(key);
	auto blockFields = block::read(blockNumber);
	if(search::elementWithKeyExists(blockFields, key))
		return false;
	if((blockFields.size()>=databaseConfiguration::blockFieldsNumber)||(blockNumber<0))
	{
		overflowArea::addNewField(key, value);
	}
	else
	{
		blockFields.emplace_back(key, value);
		block::sortByKey(blockFields);
		block::write(blockNumber, blockFields);
	}
	return true;
}
