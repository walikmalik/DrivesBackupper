#include "Configuration.h"
#include "..\Configuration.h"

Configuration::Configuration(DWORD volumeSerialNumber, char * backupPath)
{
	this->volumeSerialNumber = volumeSerialNumber;
	this->backupPath = backupPath;
}
