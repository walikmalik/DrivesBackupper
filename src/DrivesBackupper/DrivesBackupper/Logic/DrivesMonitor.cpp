#include "DrivesMonitor.h"
#include "Backupper.h"


DrivesMonitor::DrivesMonitor()
{
	this->existingDrives = "";
	this->newDrives = "";
}


DrivesMonitor::~DrivesMonitor()
{
}

void DrivesMonitor::execute()
{
	readDrives();
	this->existingDrives = this->newDrives;

	while (true)
	{
		//TODO: Low system priority.
		DWORD ldSize = readDrives();

		if (this->newDrives.find_first_not_of(this->existingDrives) != this->newDrives.npos)
			runBackupper(returnNewElement(ldSize));
		else if (this->existingDrives.find_first_not_of(this->newDrives) != this->newDrives.npos)
			this->existingDrives = this->newDrives;
	}
}

DWORD DrivesMonitor::readDrives()
{
	TCHAR newDrivesBuff[BUFSIZE];
	DWORD size = GetLogicalDriveStrings(BUFSIZE, newDrivesBuff);

	this->newDrives = "";

	for (int i = 0; i < size - 1; ++i)
	{
		//Searching A-Z ASCII code
		if (newDrivesBuff[i] >= 65 && newDrivesBuff[i] <= 90)
		{
			this->newDrives += newDrivesBuff[i];
		}
	}

	return size;
}

TCHAR DrivesMonitor::returnNewElement(DWORD size)
{
	TCHAR driveMark = this->newDrives[this->newDrives.find_first_not_of(this->existingDrives)];

	if (driveMark != this->existingDrives.npos)
	{
		this->existingDrives = this->newDrives;
		return driveMark;
	}

	return (TCHAR)"";
}

void DrivesMonitor::runBackupper(TCHAR driveMark)
{
}