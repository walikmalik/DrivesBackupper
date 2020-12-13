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
	else
	{
		switch (showInstallingMessage(driveMark))
		{
		case  6:
			runNewDriveInstaller();
			break;
		default:
			break;
		}
	}
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

bool Backupper::showInstallingMessage(TCHAR driveMark)
{
	string message = "Drive ";
	message += driveMark;
	message += MESSAGE_INSTALL_TEXT;

	messageBoxAnswer = MessageBox(NULL, message.c_str(), "New drive.", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
	return false;
}

void Backupper::runNewDriveInstaller()
{
	driveInstaller.Execute(volumeSerialNumber);
}