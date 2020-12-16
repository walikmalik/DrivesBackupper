#include "Actions.h"

namespace fs = std::filesystem;

Actions::Actions()
{
}

Actions::~Actions()
{
}

void Actions::execute(DWORD driveMark, Configuration config)
{
	this->config = config;

	drivePath += driveMark;
	drivePath += ":\\";

	if (ifDirectoryEmpty(drivePath))
		return;

	if (!PathIsDirectory(config.backupPath.c_str()))
		createBackupDirectory(config.backupPath);

	if (findNewFiles())
		copyNewFiles();
}

bool Actions::ifDirectoryExist(string path)
{
	return !PathIsDirectoryEmptyA(path.c_str());
}

bool Actions::ifDirectoryEmpty(string path)
{
	return PathIsDirectoryEmptyA(path.c_str());
}

set<string> Actions::readFileNames(string path)
{
	set<string> pathFiles;
	try
	{
		for (const auto & begin : fs::directory_iterator(path))
			pathFiles.insert(begin.path().string());
	}
	catch (fs::filesystem_error& e)
	{
	}
	return pathFiles;
}

bool Actions::findNewFiles()
{
	driveFiles = readFileNames(drivePath);
	driveBackuppedFiles = readFileNames(config.backupPath);

	if (driveFiles == driveBackuppedFiles)
		return false;
	else if (driveFiles > driveBackuppedFiles)
		return true;

	return false;
}

void Actions::copyNewFiles()
{
	set<string> toCopy;
	set_difference(driveFiles.begin(), driveFiles.end(),
		driveBackuppedFiles.begin(), driveBackuppedFiles.end(),
		inserter(toCopy, toCopy.begin()));


		for (const auto & begin : toCopy)
		{
			string targetLocation = config.backupPath;
			targetLocation += catchFileName(begin);
			try
			{
				fs::copy_file(begin, targetLocation);
			}
			catch (fs::filesystem_error& e)
			{
			}
		}
}

string Actions::catchFileName(string path)
{
	string fileName;
	for (const auto & begin : path)
	{
		if (begin != '\\')
			fileName += begin;
		else
			fileName = begin;
	}
	
	return fileName;
}

void Actions::createBackupDirectory(string path)
{
	try
	{
		fs::create_directory(path.c_str());
	}
	catch (fs::filesystem_error& e)
	{
	}
}
