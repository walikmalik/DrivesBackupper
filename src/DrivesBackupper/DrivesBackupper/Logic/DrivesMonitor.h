#pragma once

#undef DEBUG

#include "Backupper.h"

#include <windows.h>
#include <string>
#include <set>
#include <map>
#include <thread>
#include <memory>
#include <processthreadsapi.h>

#ifdef DEBUG
#include <iostream>
#endif // DEBUG


#define BUFSIZE 512

using namespace std;

class DrivesMonitor
{
private:
	map <TCHAR, shared_ptr<Backupper>> backupperInstances;
	map <TCHAR, thread> backupperThreads;
	set<DWORD> doNotAskAgainDrives;

	string existingDrives;
	string newDrives;

	DWORD readDrives();
	TCHAR returnNewElement();
	TCHAR returnLackElement();
	void runBackupper(TCHAR driveMark);
	void stopBackupper(TCHAR driveMark);
	void checkBackuppersStatus();

public:
	DrivesMonitor();
	~DrivesMonitor();

	void execute();
};

