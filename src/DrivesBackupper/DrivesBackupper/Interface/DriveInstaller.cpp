#include "DriveInstaller.h"



DriveInstaller::DriveInstaller()
{
}


DriveInstaller::~DriveInstaller()
{
}

void DriveInstaller::Execute(DWORD volumeSerialNumber)
{
	this->volumeSerialNumber = volumeSerialNumber;
}
