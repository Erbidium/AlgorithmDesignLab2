#include <iostream>
#include <fstream>
#include <filesystem>

#include "database.h"

using namespace std;

int main()
{
    cout<<databaseConfiguration::blocksNumber<<endl;
    srand(time(NULL));
    cout<<"Add new field(0)\n Edit field(1)\n Delete field(2)";
    int actionChoice;
	if(actionChoice==0)
	{
		
	}
    else if(actionChoice==1)
    {
	    
    }
    else if(actionChoice==2)
    {
	    
    }
    if(!filesystem::exists(databaseConfiguration::indexFileName)||(!filesystem::exists(databaseConfiguration::dataFileName)))
    {
	    database::createIndexFile();
        database::createDataFile();
        database::generateDataFile();
    }
    database::printBlock(13);
    if(!database::addNewField(3330, "hello world!"))
    {
    	cout<<"Sorry, element with such key already exists!"<<endl;
    }
    database::printBlock(13);
}