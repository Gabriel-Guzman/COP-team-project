#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <limits>
#include "fileObject.h"
#include "memory.h"
#include "dirent.h"
#include "FileIO.h"

using namespace std;
vector<string> splitString(string);

int main()
{

    vector<string> stuff;
    stuff.push_back("tag1");
    stuff.push_back("tag2");

    string cheese = "cheese";

    // should be its own function, necessary to initialize memoryVector
    vector<fileObject> init;
    memory test(init);
    test.initializeMemory();

    /*
    test.createFileObject(stuff, cheese);


    string fileName1 = "beans";
    stuff.clear();
    stuff.push_back("red");
    stuff.push_back("blue");
    test.createFileObject(stuff, fileName1);

    string fileName2 = "carrots";
    stuff.clear();
    stuff.push_back("eight");
    stuff.push_back("twelve");
    test.createFileObject(stuff, fileName2*/
    
    int choice;
    string tag1;
    string tag;
    string file;
    bool keepGoing = true;
    char y[1000];
    vector<string> fileList;
    int counter;
    int enormity;

    stuff.clear();

    while(keepGoing)
    {
        //1 addtag, 2 deleteTag, 3 print, 4 search, 5 stringifyMemory, 6 quit
        cout<<"1. Add a tag\n2. Delete a tag\n3. Print\n4. Search\n5. Save\n6. Quit"<<endl;
        cin>>choice;
        while (choice >10 || choice < 1 || cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"Invalid Input"<<endl;
            cin>>choice;
        }

        switch(choice)
        // takes one string at a time.
        {
            case 1:
                cout<<"to what file?"<<endl;
                cin>>file;
                cout<<"what tags?"<<endl;
                // this takes in whole line cin as a string tag
                // converts char array into vector of individual words.
                cin>>tag1;
                cin.getline(y, 1000);
                tag = y;
                tag = tag1+ tag;
                stuff = splitString(tag);

                /// takes one string at a time
                for (unsigned int i =0; i<stuff.size(); i++)
                {
                        test.switchAdd(stuff[i], file);
                }
                break;
            case 2:
                cout<<"from what file?"<<endl;
                cin>>file;
                cout<<"what tag?"<<endl;
                cin>>tag;

                test.deleteTagFromFile(file, tag);
                break;

            case 3:
                test.printMemory();
                break;

            case 4:
                cout<<"What tag would you like to search for?"<<endl;
                cin>>tag;
                fileList = test.searchForFilesWithTag(tag);

                counter = 0;
                enormity = fileList.size();
                cout<<"Files with tag '"<<tag<<"': ";
                while (counter < enormity)
                {
                    cout<<fileList[counter]<<" ";
                    counter++;
                }
                break;

            case 5:
                test.stringifyMemory();
                break;
            case 6:
                keepGoing=false;
                break;
        }
        cout<<endl;
    }

    return 0;
}


vector<string> splitString(string tagString)
 {
    string buf; // Have a buffer string
    stringstream ss(tagString); // Insert the string into a stream

    vector<string> tags; // Create vector to hold our words

    while (ss >> buf)
        tags.push_back(buf);

     return tags;
}
