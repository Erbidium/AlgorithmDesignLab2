#include <iostream>
#include <fstream>
#include <filesystem>

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
	    cout<<endl<<"Edit database or find field(0)\nPrint database(1)\nClear database(2)\nRandom fill database(3)\nExit(4)"<<endl;
	    int actionChoice = 0;
	    cin>>actionChoice;
		if(actionChoice==0)
		{
			cout<<endl<<"Add new field(0)\nEdit field(1)\nDelete field(2)\nFindField(3)\nBack to main menu(4)"<<endl;
			int fieldChoice = 0;
			cin>>fieldChoice;
			if((fieldChoice>=0)&&(fieldChoice<=3))
			{
				cout<<endl<<"Enter positive key of the element: ";
				int key;
				cin>>key;
				if(key>=0)
				{
					std::string value;
					if(fieldChoice==0||fieldChoice==1)
					{
						cout<<endl<<"Enter value with non-zero coded symbols and without whitespaces: ";
						cin>>value;
					}
					int comparisonsNumber = 0;
					if(fieldChoice == 0)
					{
					    if(!field::addNew(key, value, comparisonsNumber))
					    {
							dataFile::print();
    						cout<<endl<<"Sorry, element with such key already exists!"<<endl;
					    }
						else
						{
							dataFile::print();
							cout<<endl<<"Success!"<<endl;
						}
						cout<<"Comparisons number: "<<comparisonsNumber<< endl<<endl;
					}
					else if(fieldChoice == 1)
					{
						if(!field::editValue(key, value, comparisonsNumber))
						{
							dataFile::print();
							cout<<endl<<"Such element doesn't exist!"<<endl;
						}
						else
						{
							dataFile::print();
							cout<<endl<<"Success!"<<endl;
						}
						cout<<"Comparisons number: "<<comparisonsNumber<< endl<<endl;
					}
					else if(fieldChoice == 2)
					{
						if(!field::deleteByKey(key, comparisonsNumber))
						{
							dataFile::print();
							cout<<endl<<"Such element doesn't exist!"<<endl;
						}
						else
						{
							dataFile::print();
							cout<<endl<<"Success!"<<endl;
						}
						cout<<"Comparisons number: "<<comparisonsNumber<< endl<<endl;
					}
					else if(fieldChoice == 3)
					{
						string foundValue;
						if(!field::searchByKey(key, foundValue, comparisonsNumber))
						{
							dataFile::print();
							cout<<endl<<"Such element doesn't exist!"<<endl;
						}
						else
						{
							dataFile::print();
							cout<<endl<<"Success!"<<endl;
							cout<<"Value: "<<foundValue<<endl;
						}
						cout<<"Comparisons number: "<<comparisonsNumber<< endl<<endl;
					}
				}
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
	    }
	    else if(actionChoice==3)
	    {
			cout<<endl<<"Enter number of elements in block: ";
			int numberOfBlockElements;
			cin>>numberOfBlockElements;
			cout<<endl<<"Enter number of elements in overflow area: ";
			int numberOfOverflowAreaElements;
			cin>>numberOfOverflowAreaElements;
	    	dataFile::generate(numberOfBlockElements, numberOfOverflowAreaElements);
	    }
	    else if(actionChoice==4)
	    {
		    exit=true;
	    }
		else
		{
			cout<<endl<<"Wrong choice! Try to choose something again!"<<endl;
		}
    }
}