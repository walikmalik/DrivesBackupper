#pragma once

#include <tchar.h>
#include <windows.h>
#include <string>
#include <thread>

using namespace std;

class Backupper
{
private:
	DWORD volumeSerialNumber;

	void identify(TCHAR driveMark);
public:
	Backupper();
	~Backupper();

	void execute(TCHAR driveMark);
};

