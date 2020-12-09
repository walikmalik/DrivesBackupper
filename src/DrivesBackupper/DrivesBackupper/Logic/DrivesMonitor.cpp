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
		{
#ifdef DEBUG
			std::cout << "New drive detected.\n";
#endif // DEBUG
			runBackupper(returnNewElement());
		}
		else if (this->existingDrives.find_first_not_of(this->newDrives) != this->newDrives.npos)
		{
#ifdef DEBUG
			std::cout << "Drive disconnected.\n";
#endif // DEBUG
			stopBackupper(returnLackElement());
		}
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

TCHAR DrivesMonitor::returnNewElement()
{
	TCHAR driveMark = this->newDrives[this->newDrives.find_first_not_of(this->existingDrives)];

	if (driveMark != this->existingDrives.npos)
	{
		this->existingDrives = this->newDrives;
		return driveMark;
	}

	return (TCHAR)"";
}

TCHAR DrivesMonitor::returnLackElement()
{
	TCHAR driveMark = this->existingDrives[this->existingDrives.find_first_not_of(this->newDrives)];

	if (driveMark != this->newDrives.npos)
	{
		this->existingDrives = this->newDrives;
		return driveMark;
	}

	return (TCHAR)"";
}

void DrivesMonitor::runBackupper(TCHAR driveMark)
{
	shared_ptr<Backupper> currentPtr = shared_ptr<Backupper>(new Backupper());

	backupperInstances.insert(pair<TCHAR, shared_ptr<Backupper>>(driveMark, currentPtr));
	backupperThreads.insert(pair<TCHAR, thread>(driveMark, thread(&Backupper::execute, ref(*currentPtr), driveMark)));
}

void DrivesMonitor::stopBackupper(TCHAR driveMark)
{
	backupperThreads.at(driveMark).detach();
	backupperThreads.erase(backupperThreads.find(driveMark));

	backupperInstances.erase(backupperInstances.find(driveMark));
}