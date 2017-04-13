#ifndef FILEOBJECT_H
#define FILEOBJECT_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class fileObject
{
    /*
        fileObject will store two data types.
        the tagVector will keep all of the tags asscoiated with the object
        that were added by the user.
        The fileName is how we will identify the object and and its corresponding
        file, this will be used to identify it within the memoryVector
        and also looking for it within the directory
    */
    private:
        vector<string> tagList;
        string fileName;

    public:
        fileObject(vector<string>&, string);
        void addTag(string);
        bool deleteTag(string);
        void printTagList();
        bool checkForTag(string tag);
        void stringifyFileObject();
        string returnFileName();
        vector<string>& getTagList();
        string commaDeleter(string checkString);
        bool commaPositionChecker (string checkString);
        bool commaChecker(string checkString);


};

// constructor if this is a file with no tags yet
fileObject::fileObject(vector<string>& newVectorTag, string newFileName)
{
    tagList = newVectorTag;
    fileName= newFileName;
}

vector<string>& fileObject::getTagList()
{
    return tagList;
}

string fileObject::returnFileName()
{
    return fileName;
}

// this class will add a new tag to the vectorTag
void fileObject::addTag(string tag)
{
    string temp = commaDeleter(tag);
    tagList.push_back(temp);
}

/*
    this will search through the vectorTag for a string called tag
    and delete it.
    we will also check if the vector tag is empty, if it is we will
    will return true so that the memoryVector class can remove the unneeded
    fileObject
*/
// does this tag actually exist, need a safe guard either as a class here or within
// memoryVector
bool fileObject::deleteTag(string tag)
{
    // search through tag and gets specific index value for the tag
    int enormity = tagList.size();
    int index = 0;
    int counter = 0;

    while (counter < enormity)
    {
        if (tagList[counter] == tag)
        {
            index = counter;
        }
        counter++;
    }
    //cout<<"index: "<<index<<endl;

    // need to do the begin thing, index by itself does not work
    tagList.erase(tagList.begin()+ index);

    // now we will check and return if vectorTag is empty
    bool isEmpty = false;

    if (tagList.size()== 0)
    {
        isEmpty = true;
    }

    return isEmpty;
}

// this is going to print out all the tags- duh
void fileObject::printTagList()
{
    int enormity = tagList.size();

    int counter = 0;
    cout<<fileName<<": ";
    while (counter < enormity)
    {
        // if deals with extra comma at end
        if (counter == enormity -1)
        {
            cout<<tagList[counter];
            break;
        }
        cout<<tagList[counter]<< ", ";
        counter++;

    }
    cout<<endl;

}

// this will search through tagList and return true if the tag exist,
// part of a failsafe to avoid deleting nonexistent tags or adding multiples
// of the same tag
// returns true if tag exist
bool fileObject::checkForTag(string tag)
{
    int enormity = tagList.size();
    int counter = 0;
    bool tagExist = false;

    while (counter < enormity)
    {
        if (tagList[counter]==tag)
        {
            tagExist = true;
        }
        counter++;
    }

    return tagExist;
}

// add file name and vector tag to a file
// this will be how we store tags when program is closed
// on opening, the program will read the file and new fileObjects initialized
void fileObject::stringifyFileObject()
{
    ofstream memoryFile;
    memoryFile.open ("memoryFile.txt", fstream::in | fstream::out | fstream::app);

    int enormity = tagList.size();
    int counter = 0;

    memoryFile<<fileName<<": ";

    while (counter< enormity)
    {
        memoryFile<<tagList[counter]<<" ";
        counter++;
    }
    memoryFile<<endl;
    memoryFile.close();
}

//This method checks to see if there is a comma in a string.
bool fileObject::commaChecker(string checkString)
{
    bool checker = false;
    int commaIndex = checkString.find(",");
    if (commaIndex < 1000000)
        checker = true;
    return checker;
}

//This method checks to verify that a comma is at the end of a string.
bool fileObject::commaPositionChecker (string checkString)
{
    bool isEnd = false;
    int commaIndex = checkString.find(",");
    if (commaIndex == (checkString.length() - 1))
        isEnd = true;
    return isEnd;
}

//This method deletes a string's comma if it has one at the end.
string fileObject::commaDeleter(string checkString)
{
    bool hasComma = commaChecker(checkString);
    bool isEnd = commaPositionChecker(checkString);
    string returnString = "";
    if (!hasComma)
        returnString = checkString;
    else if (hasComma && isEnd)
    {
        string temp = checkString;
        int index = checkString.find(",");
        temp = checkString.substr(0, index);
        returnString = temp;
    }
    return returnString;
}
#endif // FILEOBJECT_H
