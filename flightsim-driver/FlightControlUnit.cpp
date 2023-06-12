#include "FlightControlUnit.h"
#include <iostream>

typedef enum
{
	EVENT_AUTO_THROTTLE_ARM_TOGGLE,
} EventType;

bool FlightControlUnit::EventsInitialize()
{
	bool initOk = true;
	
	bool tmpOk = _simServices->SetUpSimEvent(0, EVENT_AUTO_THROTTLE_ARM_TOGGLE, "AUTO_THROTTLE_ARM");
	if (tmpOk != true)
		initOk = false;

	return initOk;
}

FlightControlUnit::FlightControlUnit(const SimServices& simServices)
	: ModuleHardware(simServices)
{
	_name = "FCU";
}

void FlightControlUnit::Initialize()
{
	PrintInitMessage();

	bool initOk = EventsInitialize();

	std::cout << _name << " Event setup " << (initOk == true ? "finished" : "failed") << "\r\n";
}

void FlightControlUnit::Manage()
{

}
