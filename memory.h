#ifndef MEMORY_H
#define MEMORY_H
#include "fileObject.h"

class memory
{
    private:
        vector<fileObject> memoryVector;

    public:
        memory(vector<fileObject> &);
        void stringifyMemory();
        // need to improve this to search for multiple tags or
        // has certain tags but does not have others
        vector<string> searchForFilesWithTag(string);
        void createFileObject(vector<string>&, string);
        int checkFileExistence(string);
        void addTagToFile(int, string);
        // this currently only deletes one tag input at a time
        void deleteTagFromFile(string, string);
        //void deleteFileObject(string); not sure if needed

        // Loads the previously saved file objects to memory. Only to be used once on creation
        bool initializeMemory();

        void printMemory();
        void switchAdd(vector<string>&, string);
        vector<string>& lowerCase(vector<string>&);
        vector<string>& deleteDuplicates(vector<string>&, int index);

};

// passing by reference to make the run cost less
memory::memory(vector<fileObject> &init)
{
    memoryVector = init;
}

bool memory::initializeMemory(){
    bool worked = false;
    ifstream ifs;
    ifs.open("memoryFile.txt", ios::in);

    string current_line;
    string temp_filename;
    string temp_tag;
    if(ifs.is_open()){
        worked = true;
        while(getline(ifs, current_line)){
            stringstream ss(current_line);

            while(cout << ss);

            ss.str("");
            ss.clear();
        }
    }
    return worked;
}
/*
    This method checks if any of the tags to be added in the vector are duplicates,
    it also compares to the tagVector of the file object and searches for duplicates.
    if there are any duplicates the method deletes those tags before returning the vector
*/
/// this method is not super failsafe and if you add ten duplicates mixed with regular tags it will fail
vector<string>& memory::deleteDuplicates(vector<string>& tags, int index)
{
    // run through a loop to check for any duplicate tags
    // it pushes back the duplicates, but does not repeatedly hit doubles
    vector<int> duplicates;
    for (unsigned int i = 0; i<tags.size(); i++)
    {
        for (unsigned int j=0; j<i; j++)
        {
            if (tags[i]==tags[j])
            {
                duplicates.push_back(i);
            }
        }
    }
    int counter = duplicates.size()-1;
    int toErase;

    // this erases from back to front to avoid changing index
    // of to-be-erased tags
    while (counter>= 0)
    {
        toErase = duplicates[counter];
        tags.erase(tags.begin()+toErase);
        counter--;
    }
    duplicates.clear();
    bool match;

    /*
        This will check if duplicates of the tags we are trying to add exist
        already within the fileObject. If they do they are added to the duplicate vector
        to be deleted later.
    */
    for (unsigned int i = 0; i<tags.size(); i++)
    {
        match = memoryVector[index].checkForTag(tags[i]);
        if (match)
        {
            duplicates.push_back(i);
        }
    }

    counter= duplicates.size()-1;
     while (counter>= 0)
    {
        toErase = duplicates[counter];
        tags.erase(tags.begin()+toErase);
        counter--;
    }

    return tags;
}

/*
    This function will take in the tags you want to add to a
    certain file. If that file does not yet exist in the memoryVector,
    then it will be created with createFileObject. Otherwise
    we will continually add tags from the vector in a loop to the
    designated fileObject.
    Assumes that a nonexistent directory file will not be input
*/
void memory::switchAdd(vector<string>& tags, string file)
{
    // changes the tags to lower case
    tags = lowerCase(tags);
    // checks for repetition of tags in vector or target file
    int index = checkFileExistence(file);

    tags = deleteDuplicates(tags, index);

    if (index == -1)
    {
        createFileObject(tags, file);
    }
    else
    {
        int enormity = tags.size();
        int counter= 0;

        while (counter <enormity)
        {
            memoryVector[index].addTag(tags[counter]);
            counter++;
        }
    }
}

// initializes fileObject and the adds it to the memoryVector
// this should be done if check fileExistence returns -1!
void memory::createFileObject(vector<string>& tags, string file)
{
    fileObject cell(tags, file);
    memoryVector.push_back(cell);
}

// iterates through memory vector and calls print function for file object
void memory::printMemory()
{
     int enormity = memoryVector.size();
     int counter = 0;

     // loops through every object in vector
     while (counter < enormity )
     {
         memoryVector[counter].printTagList();
         counter++;
     }
}

// returns index of fileObject within memoryVector
// if the object is not found then this returns -1
// this speeds process of adding tags and also safeguards
// against adding tag to nonexistent file
int memory::checkFileExistence(string name)
{
    int counter = 0;
    int enormity = memoryVector.size();
    int index = -1;
    string fileObjectName;

    while (counter < enormity)
    {
        fileObjectName= memoryVector[counter].returnFileName();

        if (name == fileObjectName)
        {
            index = counter;
        }
        counter++;
    }

    return index;
}

/*
    Adds tag to file assuming that checkFileExistence has already been
    called and is returning an index.
*/
void memory::addTagToFile(int index, string tag)
{
    memoryVector[index].addTag(tag);
}

/*
    searches through memoryVector for tags existence. If it exist then
    fileObject deleteTag will be called. Otherwise this method will notify
    user that the file they are trying to delete from does not have any tags.

    If within the file object the tag is nowhere to be found then this method
    (memory::deleteTagFromFile) will notify user.

    If the deleteTag is successful and there are no more tags within that
    fileObjects tagList, this method will call a deletefileObject method to remove
    that fileObject from the memoryVector and free its space.
*/
void memory::deleteTagFromFile(string file, string tag)
{
    int index = checkFileExistence(file);
    if (index == -1)
    {
        cout<<"That file either doesn't exist or does not have any tags in it.";
        cout<<endl<<endl;
        return;
    }

    bool tagExist;

    tagExist= memoryVector[index].checkForTag(tag);

    if (!tagExist)
    {
        cout<<"That file does not have tag '"<<tag<<"' to delete";
        cout<<endl<<endl;
        return;
    }

    bool isEmpty;

    isEmpty = memoryVector[index].deleteTag(tag);

    if (isEmpty)
    {
        memoryVector.erase (memoryVector.begin()+ index);
    }

}

/*
    will call the checkForTag method for each object in memoryVector.
    if it finds that tag the name of the file containing that tag will
    be added to a stringVector.
    This is useful when attempting to delete a tag from every file that
    has that tag. This is also important when the user wants to search
    for files that only contain that tag.
*/
vector<string> memory::searchForFilesWithTag(string tag)
{
    int counter = 0;
    int enormity = memoryVector.size();
    bool tagExist;
    string file;

    vector<string> fileList;

    while (counter < enormity)
    {
        tagExist= memoryVector[counter].checkForTag(tag);

        if (tagExist)
        {
            file = memoryVector[counter].returnFileName();
            fileList.push_back(file);
        }
        counter++;
    }

    // Not really sure how we want to deal with this when user searches
    // For non existent tag. This method must return something so we may
    // need to catch if the fileList is empty from somewhere else.
    // Good idea to only allow user to search for tags from list of already
    // existing ones. Maybe keep a list of used tags that we can compare their
    // search input too.
    if (fileList.size() == 0)
    {
        //cout<<"No file has tag: '"<<tag<<"'";
    }

    return fileList;
}
/*
    goes through the memory vector and calls stringify fileObject for each element
    This prints the fileObjects name and tags to a file called memoryFile.txt.

    The file will be used to initialize the new memoryVector on startup.

    This method should be called only when the program is closing down, and assumes
    the user will terminate the program through an input command and not just x out.
    IF THE PROGRAM IS NOT SHUT DOWN CORRECTLY WE WILL LOSE ANY CHANGES MADE.

    so it may be necessary to perform this function at regular intervals to save changes
    and also notify the user of the importance of exiting the program correctly
*/
void memory::stringifyMemory()
{
    // this wipes all of the previous text in the file
    // avoids rewriting same data to file
    ofstream memoryFile;

    memoryFile.open("memoryFile.txt", std::ofstream::out | std::ofstream::trunc);
    memoryFile.close();

    int counter = 0;
    int enormity = memoryVector.size();

    while (counter < enormity)
    {
        memoryVector[counter].stringifyFileObject();
        counter++;
    }

}

// takes all the tags to be added and changes them to lower case
vector<string>& memory::lowerCase(vector<string>& tags)
{
    string myTag;
    //takes string from vector, changes it to lower case, then replaces
    // it with the old string
    for (unsigned int i = 0; i<tags.size(); i++)
    {
        myTag = tags[i];

        transform(myTag.begin(), myTag.end(), myTag.begin(), ::tolower);

        tags[i] = myTag;
    }
    return tags;
}

#endif // MEMORY_H
