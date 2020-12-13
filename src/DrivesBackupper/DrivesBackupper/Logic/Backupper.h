#pragma once

#undef DEBUG

#define MESSAGE_LENGTH 320
#define MESSAGE_INSTALL_TEXT ": are not installed in DrivesBackupper.\n Do you want do this now?"

#include "../Configuration.h"
#include "Actions.h"
#include "../Interface/DriveInstaller.h"

#include <tchar.h>
#include <windows.h>
#include <string>
#include <thread>
#include <processthreadsapi.h>
#include <WinUser.h>

#ifdef DEBUG
#include <iostream>
#endif // DEBUG


using namespace std;

class Backupper
{
private:
	DWORD volumeSerialNumber;
	int messageBoxAnswer;

	void identify(TCHAR driveMark);
	bool ifVolumeConfigExist();
	bool showInstallingMessage(TCHAR driveMark);
	void runNewDriveInstaller();

	Configuration config;
	Actions actions;
	DriveInstaller driveInstaller;

public:
	Backupper();
	~Backupper();

	void execute(TCHAR driveMark);
};

