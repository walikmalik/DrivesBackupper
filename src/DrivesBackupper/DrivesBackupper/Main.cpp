#undef DEBUG

#include "Logic/DrivesMonitor.h"

#include <memory>
#include <Windows.h>

int main()
{
#ifndef DEBUG
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // !DEBUG

	std::unique_ptr<DrivesMonitor> drivesMonitor;
	drivesMonitor = std::unique_ptr<DrivesMonitor>(new DrivesMonitor());
	drivesMonitor->execute();
	return 0;
}