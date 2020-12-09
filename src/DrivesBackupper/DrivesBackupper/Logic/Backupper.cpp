#include "Backupper.h"



Backupper::Backupper()
{
}


Backupper::~Backupper()
{
}

void Backupper::execute(TCHAR driveMark)
{
	identify(driveMark);
}

void Backupper::identify(TCHAR driveMark)
{
	GetVolumeInformationA(driveMark + ":\\", NULL, NULL, &volumeSerialNumber, NULL, NULL, NULL, NULL);
#ifdef DEBUG
	cout << "\nDrive identified.\nVolume Serial Number: " << volumeSerialNumber << "\n";
#endif // DEBUG

}