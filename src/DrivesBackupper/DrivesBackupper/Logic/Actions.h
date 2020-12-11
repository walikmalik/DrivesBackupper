#pragma once
#include "../Configuration.h"

#include <string>
#include <set>
#include <shlwapi.h>
#include <filesystem>
#include <iterator>

using namespace std;

class Actions
{
private:
	Configuration config;

	string drivePath;
	set<string> driveFiles;
	set<string> driveBackuppedFiles;

	bool ifNotEmpty(string path);
	bool ifEmpty(string path);
	set<string> readFileNames(string path);
	bool findNewFiles();
	void copyNewFiles();
	string catchFileName(string path);
	void createBackupDirectory(string path);
public:
	Actions();
	~Actions();

	void execute(DWORD driveMark);
};

