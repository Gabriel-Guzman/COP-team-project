
#ifndef FILEIO_H
#define FILEIO_H



bool is_in_vector(vector<string> v, string to_find) {
	return (find(v.begin(), v.end(), to_find) != v.end());
}

class FileIO {
private:
	//This is a list of the files in the current working directory
	vector<string> cwd_files;
	bool success;
public:
	FileIO();
	// This method will parse fileName and create fileObjects, that will be pushed to mem
	bool worked();
	// Check if worked before calling get files to avoid unexpected behavior
	void sync(memory& memoryFiles);
	// Syncs memory and cwd files by adding all missing cwd files into memory AND deleting all noncwd files from memory

	vector<string> get_files();

};

//On construction, FileIO creates the list of files in our directory.
FileIO::FileIO() {
	success = false;

	DIR *dir;
    struct dirent *ent;
    string ban1 = ".";
    string ban2 = "..";
	if ((dir = opendir ("./")) != NULL) {

	while ((ent = readdir (dir)) != NULL) {
		if(ban1.compare(ent->d_name) != 0 && ban2.compare(ent->d_name))
			cwd_files.push_back(ent->d_name);

	}
	closedir (dir);
	} else {
		// could not open directory
		perror ("");

	}
	success = true;
}



bool FileIO::worked(){
	return success;
}

vector<string> FileIO::get_files(){
	return cwd_files;
}

//This function deletes files in memory if they don't exist anymore on disk, and creates new files in memory
// if they're new on the disk. This will let us keep an updated list of files.
void FileIO::sync(memory &memoryFiles){

	if(!worked()) {
		cout << "Failed to get files, can't sync." << endl;
	} else {
		vector<string> cwdFiles = get_files();
		for(unsigned int i; i < cwdFiles.size(); i++){
			if(memoryFiles.checkFileExistence(cwdFiles[i]) == (-1)){
				vector<string> emptyTagList;
				memoryFiles.createFileObject(emptyTagList, cwdFiles[i]);
			}
		}


		vector<fileObject> temp = memoryFiles.getMemory();

		for(unsigned int i; i < temp.size(); i++){
			if(!is_in_vector(cwdFiles, temp[i].returnFileName())){
				memoryFiles.deleteFileObject(temp[i].returnFileName());

			}
		}
	}


}

#endif