#include "Actions.h"

namespace fs = std::filesystem;

Actions::Actions()
{
}

Actions::~Actions()
{
}

void Actions::execute(DWORD driveMark)
{
	drivePath += driveMark;
	drivePath += ":\\";

	if (ifNotEmpty())
	{
		if (findNewFiles())
			copyNewFiles();
	}
}

bool Actions::ifNotEmpty()
{
	return !PathIsDirectoryEmptyA(drivePath.c_str());
}

set<string> Actions::readFileNames(string path)
{
	set<string> pathFiles;
	for (const auto & begin : fs::directory_iterator(path))
		pathFiles.insert(begin.path().string());

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
