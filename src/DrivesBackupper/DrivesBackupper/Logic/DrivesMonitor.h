#pragma once

#include "Backupper.h"

#include <windows.h>
#include <string>
#include <vector>
#include <tchar.h>


#define BUFSIZE 512

using namespace std;

class DrivesMonitor
{
private:
	Backupper backupper;

	string existingDrives;
	string newDrives;

	DWORD readDrives();
	TCHAR returnNewElement(DWORD size);
	void runBackupper(TCHAR driveMark);

public:
	DrivesMonitor();
	~DrivesMonitor();

	void execute();
};

