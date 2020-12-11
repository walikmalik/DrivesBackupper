#pragma once

#undef DEBUG

#include "../Configuration.h"
#include "Actions.h"

#include <tchar.h>
#include <windows.h>
#include <string>
#include <thread>
#include <processthreadsapi.h>

#ifdef DEBUG
#include <iostream>
#endif // DEBUG


using namespace std;

class Backupper
{
private:
	DWORD volumeSerialNumber;

	void identify(TCHAR driveMark);
	bool ifVolumeConfigExist();

	Configuration config;
	Actions actions;

public:
	Backupper();
	~Backupper();

	void execute(TCHAR driveMark);
};

