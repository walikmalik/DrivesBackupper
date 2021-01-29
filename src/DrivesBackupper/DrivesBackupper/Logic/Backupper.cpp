#include "Backupper.h"



Backupper::Backupper()
{
}


Backupper::~Backupper()
{
}

void Backupper::execute(TCHAR driveMark)
{
	finished = false;

	SetPriorityClass(this, NORMAL_PRIORITY_CLASS);
	identify(driveMark);
	readConfigFile();

	set<Configuration>::iterator iter = VolumeConfig();
	if (iter != installedDrives.end())
	{
		config.volumeSerialNumber = iter->volumeSerialNumber;
		config.backupPath = iter->backupPath;
		
		actions.execute(driveMark, config);
	}
	else
	{
		switch (showInstallingMessage(driveMark))
		{
		case  6:
			runNewDriveInstaller();
			execute(driveMark);
			break;
		case 7:
			doNotAskAgainDrives = true;
			break;
		default:
			doNotAskAgainDrives = false;
			break;
		}
	}
	finished = true;
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

set<Configuration>::iterator Backupper::VolumeConfig()
{
	for (set<Configuration>::iterator i = installedDrives.begin(); i != installedDrives.end(); ++i)
	{
		if (volumeSerialNumber == i->volumeSerialNumber)
			return i;
	}
	return installedDrives.end();
}

int Backupper::showInstallingMessage(TCHAR driveMark)
{
	string message = "Drive ";
	message += driveMark;
	message += MESSAGE_INSTALL_TEXT;

	return MessageBox(NULL, message.c_str(), "DrivesBackupper.", MB_YESNOCANCEL | MB_ICONEXCLAMATION);	
}

void Backupper::runNewDriveInstaller()
{
	driveInstaller.Execute(volumeSerialNumber);
}

void Backupper::readConfigFile()
{
	string configPath = "C:\\Users\\";
	configPath += getUserName();
	configPath += "\\DriveBackups\\config.txt";

	ifstream config;
	config.open(configPath, ios::out);
	if (!config.is_open())
		return;

	string fileBuffer;
	Configuration newDriveConfig;

	while (getline(config, fileBuffer)) 
	{
		stringstream buff(fileBuffer);

		while (getline(buff, fileBuffer, ' '))
		{
			if (fileBuffer == "volumeSerialNumber")
			{
				getline(buff, fileBuffer, ' ');
				newDriveConfig.volumeSerialNumber = stol(fileBuffer);
			}
			else if (fileBuffer == "backupPath")
			{
				getline(buff, fileBuffer, ' ');
				newDriveConfig.backupPath = fileBuffer;
			}
			if (newDriveConfig.backupPath != "" && newDriveConfig.volumeSerialNumber != NULL)
			{
				installedDrives.insert(newDriveConfig);
				newDriveConfig.backupPath = "";
				newDriveConfig.volumeSerialNumber = NULL;
			}
		}
	}
	config.close();
}

string Backupper::getUserName()
{
		char currentUser[MAX_USER_NAME_LENGTH + 1];
		DWORD usernameLength = MAX_USER_NAME_LENGTH + 1;
		if (!GetUserNameA(currentUser, &usernameLength))
			return NULL;
		
		return currentUser;
}
