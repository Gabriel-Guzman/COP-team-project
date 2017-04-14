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
	//void sync(memory memoryFiles);
	// Syncs memory and cwd files by adding all missing cwd files into memory AND deleting all noncwd files from memory

	vector<string> get_files();

};

FileIO::FileIO() {
	success = false;

	DIR *dir;
    struct dirent *ent;
	if ((dir = opendir ("./")) != NULL) {

	while ((ent = readdir (dir)) != NULL) {
		if(ent->d_name != "." && ent->d_name != "..")
			cwd_files.push_back(ent->d_name);

	}
	closedir (dir);
	} else {
		// could not open directory 
		perror ("");

	}
}



bool FileIO::worked(){
	return success;
}

vector<string> FileIO::get_files(){
	return cwd_files;
}


<<<<<<< HEAD
/*void FileIO::sync(memory memoryFiles){
=======
void FileIO::sync(memory memoryFiles){
>>>>>>> 3e174d27dfbbcc0838819ef46ee53db210c85bc6
	vector<string> cwdFiles = get_files();
	for(unsigned int i; i < cwdFiles.size(); i++){
		if(memoryFiles.checkFileExistence(cwdFiles[i]) == (-1)){
			vector<string> emptyTagList;
			memoryFiles.createFileObject(emptyTagList, cwdFiles[i]);
		}
	}

	for(unsigned int i; i < memoryFiles.size(); i++){
		if(!is_in_vector(cwdFiles, memoryFiles[i])){
			//TODO write delete funct
			deleteFromMemory(memoryFiles[i]);
		}
	}
}
<<<<<<< HEAD
*/
=======

bool is_in_vector(vector<string> v, string to_find) {
	return (find(v.begin(), v.end(), to_find) != v.end());
}
>>>>>>> 3e174d27dfbbcc0838819ef46ee53db210c85bc6
