#include "ModuleHardware.h"
#include <chrono>

void ModuleHardware::Initialize()
{
	PrintInitMessage();

	bool initOk = EventsInitialize();
	_console.Send(_name + " Event setup " + (initOk == true ? "finished" : "failed") + "\r\n");

	initOk = DataInitialize();
	_console.Send(_name + " Data setup " + (initOk == true ? "finished" : "failed") + "\r\n");
}

void ModuleHardware::Manage()
{
	static std::chrono::time_point<std::chrono::system_clock> lastUpdate;

	//check if data updating is active
	if (_dataUpdatePeriod < 0)
		return;

	auto timeNow = std::chrono::system_clock::now();
	auto timeDiff = timeNow - lastUpdate;

	if (timeDiff >= std::chrono::milliseconds(_dataUpdatePeriod))
	{
		_simServices.RequestData(GetID(), DATA_REQUEST_ID_PERIODIC);
		lastUpdate = timeNow;
	}
}
