#undef DEBUG

#include "Logic/DrivesMonitor.h"

#include <memory>

int main()
{
	std::unique_ptr<DrivesMonitor> drivesMonitor;
	drivesMonitor = std::unique_ptr<DrivesMonitor>(new DrivesMonitor());
	drivesMonitor->execute();
	return 0;
}