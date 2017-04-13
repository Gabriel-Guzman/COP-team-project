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

	vector<string> get_files();

}

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
		return EXIT_FAILURE;
	}
}



FileIO::worked(){
	return success;
}

FileIO::get_files(){
	return cwd_files;
}