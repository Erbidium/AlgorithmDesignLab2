#include <iostream>
#include <fstream>
#include <filesystem>
#include "database.h"

using namespace std;

int main()
{
    //cout<<databaseConfiguration::blockSizeInBytes*databaseConfiguration::blocksNumber<<endl;
    //srand(time(NULL));
    //if(!filesystem::exists("index.txt")||(!filesystem::exists("main.txt.txt")))
    //{
	    //database::createIndexFile();
        database::createDataFile();
    //}
    database::generateDataFile();
    database::printDataFile();
}