#pragma once
#define INSTALL_MESSAGE "Write backup directory or press enter to use default.\n"
#define MAX_PATH_LENGTH 256
#define MAX_USER_NAME_LENGTH 256

#include <windows.h>
#include <shlwapi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Shlobj.h>

using namespace std;
class DriveInstaller
{
public:
	DWORD volumeSerialNumber;
	string backupPath;
	string defaultPath;
	HANDLE configFile;

	bool ifDirectoryExist(string path);

	void createBackupDirectory();
	void createDefaultDirectory();
	void createConfigFile();
	void addDriveToConfig();
	void getDefaultPath();
	void getBackupPath();	//If false use default options.
	PIDLIST_ABSOLUTE showMessage(string title, string message);
	string generateDefaultPath(string suffix);
public:
	DriveInstaller();
	~DriveInstaller();
	void Execute(DWORD volumeSerialNumber);
};

