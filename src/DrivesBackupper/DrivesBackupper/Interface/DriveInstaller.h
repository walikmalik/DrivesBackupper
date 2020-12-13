#pragma once

#include <windows.h>
class DriveInstaller
{
public:
	DWORD volumeSerialNumber;
public:
	DriveInstaller();
	~DriveInstaller();
	void Execute(DWORD volumeSerialNumber);
};

