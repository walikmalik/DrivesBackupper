#include "Backupper.h"



Backupper::Backupper()
{
}


Backupper::~Backupper()
{
}

void Backupper::execute(TCHAR driveMark)
{
	SetPriorityClass(this, NORMAL_PRIORITY_CLASS);
	identify(driveMark);
	if (ifVolumeConfigExist())
		this->actions.execute(driveMark);
}

void Backupper::identify(TCHAR driveMark)
{
	string drivePath;
	drivePath += driveMark;
	drivePath += ":\\";

	GetVolumeInformationA(drivePath.c_str(), NULL, NULL, &volumeSerialNumber, NULL, NULL, NULL, NULL);
#ifdef DEBUG
	cout << "\nDrive identified.\nVolume Serial Number: " << volumeSerialNumber << "\n";
#endif // DEBUG

}

bool Backupper::ifVolumeConfigExist()
{
	if (volumeSerialNumber == config.volumeSerialNumber)
		return true;
	return false;
}
