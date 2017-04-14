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
	void sync(vector<fileObject>& memoryFiles);
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


void FileIO::sync(memory memoryFiles){
	vector<string> cwdFiles = get_files();
	for(unsigned int i; i < cwdFiles.size(); i++){
		if(memory.checkFileExistence(cwdFiles[i]) == (-1)){
			vector<string> emptyTagList;
			memory.createFileObject(emptyTagList, cwdFiles[i]);
		}
	}

	for(unsigned int i; i < memoryFiles.size(); i++){
		if(!is_in_vector(cwdFiles, memoryFiles[i])){
			deleteFromMemory(memoryFiles[i]);
		}
	}
}

bool is_in_vector(vector<string> v, string to_find) {
	return (find(v.begin(), v.end(), to_find) != v.end());
}