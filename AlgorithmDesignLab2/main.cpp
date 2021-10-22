#include <iostream>
#include <fstream>
#include <filesystem>

#include "block.h"
#include "databaseConfiguration.h"
#include "dataFile.h"
#include "field.h"
#include "indexFile.h"

using namespace std;

int main()
{
    srand(time(NULL));
    bool exit=false;
	if(!filesystem::exists(databaseConfiguration::indexFileName)||(!filesystem::exists(databaseConfiguration::dataFileName)))
    {
	    indexFile::create();
        dataFile::create();
        dataFile::generate(30, 10);
    }
    while(!exit)
    {
	    cout<<"Edit database(0)\nPrint database(1)\nClear database(2)\nExit(3)"<<endl;
	    int actionChoice = 0;
	    cin>>actionChoice;
		if(actionChoice==0)
		{
			cout<<"Add new field(0)\nEdit field(1)\nDelete field(2)\nBack to main menu(3)"<<endl;
			int fieldChoice = 0;
			cin>>fieldChoice;
			if(fieldChoice == 0)
			{
				block::print(13);
			    if(!field::addNew(3330, "hello world!"))
			    {
    				cout<<"Sorry, element with such key already exists!"<<endl;
			    }
			    block::print(13);
			}
			else if(fieldChoice == 1)
			{
				block::print(13);
				int fieldToEdit = 0;
				cout<<"Enter key of the element, which you want to edit: ";
				cin>>fieldToEdit;
				field::editValue(fieldToEdit, "Hello");
				block::print(13);
			}
			else if(fieldChoice == 2)
			{
				block::print(13);
				int keyToDelete = 0;
				cout<<"Enter key of the element, which you want to delete: ";
				cin>>keyToDelete;
				field::deleteByKey(keyToDelete);
				block::print(13);
			}
		}
	    else if(actionChoice==1)
	    {
		    dataFile::print();
	    }
	    else if(actionChoice==2)
	    {
		    filesystem::remove(databaseConfiguration::indexFileName);
			filesystem::remove(databaseConfiguration::dataFileName);
			indexFile::create();
			dataFile::create();
			cout<<"Do you want to fill data file with random data (0) Yes (any number) No?";
			int choiceFill;
			cin>>choiceFill;
			if(choiceFill==0)
			{
				dataFile::generate(25+rand()%16, 20+rand()%16);
			}
	    }
	    else if(actionChoice==3)
	    {
		    exit=true;
	    }
		else
		{
			cout<<"Wrong choice! Try to choose something again!"<<endl;
		}
    }
}