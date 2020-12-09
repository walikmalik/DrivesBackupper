#pragma once

#include "Backupper.h"

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <memory>


#define BUFSIZE 512

using namespace std;

class DrivesMonitor
{
private:
	//vector <shared_ptr<Backupper>> backupperInstances;
	//vector <thread> backupperThreads;

	map <TCHAR, shared_ptr<Backupper>> backupperInstances;
	map <TCHAR, thread> backupperThreads;

	string existingDrives;
	string newDrives;

	DWORD readDrives();
	TCHAR returnNewElement();
	TCHAR returnLackElement();
	void runBackupper(TCHAR driveMark);
	void stopBackupper(TCHAR driveMark);

public:
	DrivesMonitor();
	~DrivesMonitor();

	void execute();
};

