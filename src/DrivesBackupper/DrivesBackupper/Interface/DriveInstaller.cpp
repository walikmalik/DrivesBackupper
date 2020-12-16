#include "DriveInstaller.h"



bool DriveInstaller::ifDirectoryExist(string path)
{
	DWORD dwAttribut = GetFileAttributes(path.c_str());

	return (dwAttribut != INVALID_FILE_ATTRIBUTES &&
		(dwAttribut & FILE_ATTRIBUTE_DIRECTORY));;
}

void DriveInstaller::createBackupDirectory()
{
}

void DriveInstaller::createDefaultDirectory()
{
	if (ifDirectoryExist(defaultPath))
		return;

	defaultPath = generateDefaultPath("");
	if (!ifDirectoryExist(defaultPath))
		CreateDirectoryA(defaultPath.c_str(), NULL);
}

void DriveInstaller::createConfigFile()
{
	if(defaultPath.empty())
		getDefaultPath();

	if (!ifDirectoryExist(defaultPath))
		createDefaultDirectory();

	string configPath = defaultPath + "config.txt";
	configFile = CreateFileA(configPath.c_str(), (GENERIC_WRITE | GENERIC_READ), (FILE_SHARE_READ | FILE_SHARE_WRITE), 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
}

void DriveInstaller::addDriveToConfig()
{
	getBackupPath();

	string driveConfig = "\nvolumeSerialNumber ";
	driveConfig += to_string(volumeSerialNumber);
	driveConfig += "\nbackupPath ";
	driveConfig += backupPath;
	driveConfig += "\n";

	DWORD driveConfigBytes = driveConfig.size();
	WriteFile(configFile, driveConfig.c_str(), driveConfigBytes, NULL, NULL);
}

void DriveInstaller::getDefaultPath()
{
	defaultPath = generateDefaultPath("");
}

void DriveInstaller::getBackupPath()
{
	if (!AllocConsole())
		return;

	char userAnswer[MAX_PATH_LENGTH];

	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	cout << INSTALL_MESSAGE;
	cin.getline(userAnswer, MAX_PATH_LENGTH);

	while (backupPath.empty())
	{
		if (strlen(userAnswer) != 0 && ifDirectoryExist(userAnswer))
		{
			backupPath = userAnswer;
		}
		else if (strlen(userAnswer) == 0)
		{
			backupPath = generateDefaultPath("backup_");
		}
		else
		{
			cout << "\nDirectory not exist.\n";
			cout << INSTALL_MESSAGE;
			cin.getline(userAnswer, MAX_PATH_LENGTH);
		}

	}

	cout.clear();
	cin.clear();
	fclose(stdout);
	fclose(stdin);
	if (!FreeConsole())
	{
		//FIXME: Console don't close.
	}
}

string DriveInstaller::generateDefaultPath(string suffix)
{
	string tmpPath = "C:\\Users\\";

	char currentUser[MAX_USER_NAME_LENGTH + 1];
	DWORD usernameLength = MAX_USER_NAME_LENGTH + 1;
	if (!GetUserNameA(currentUser, &usernameLength))
		return NULL;

	tmpPath += currentUser;
	tmpPath += "\\DriveBackups\\";
	tmpPath += suffix;
	if(suffix == "backup_")
		tmpPath += to_string(volumeSerialNumber);

	return tmpPath;
}

DriveInstaller::DriveInstaller()
{
}


DriveInstaller::~DriveInstaller()
{
}

void DriveInstaller::Execute(DWORD volumeSerialNumber)
{
	this->volumeSerialNumber = volumeSerialNumber;
	createConfigFile();
	addDriveToConfig();
}
