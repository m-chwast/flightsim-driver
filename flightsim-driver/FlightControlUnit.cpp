#include <windows.h>
#include "FlightControlUnit.h"
#include <iostream>

typedef enum
{
	EVENT_AUTO_THROTTLE_ARM_TOGGLE,
} EventType;

typedef struct
{
	int32_t autopilotAutothrottleArm;
} FCUData;


bool FlightControlUnit::EventsInitialize()
{
	bool initOk = true;
	
	bool tmpOk = _simServices->SetUpSimEvent(GetID(), EVENT_AUTO_THROTTLE_ARM_TOGGLE, "AUTO_THROTTLE_ARM");
	if (tmpOk != true)
		initOk = false;

	return initOk;
}

bool FlightControlUnit::DataInitialize()
{
	bool initOk = true;

	bool tmpOk = _simServices->SetUpData(GetID(), "AUTOPILOT THROTTLE ARM", "Boolean", SIMCONNECT_DATATYPE_INT32);
	if (tmpOk != true)
		initOk = false;

	return initOk;
}

FlightControlUnit::FlightControlUnit(const SimServices& simServices, unsigned id)
	: ModuleHardware(simServices, id)
{
	_name = "FCU";
}

void FlightControlUnit::Initialize()
{
	PrintInitMessage();

	bool initOk = EventsInitialize();
	std::cout << _name << " Event setup " << (initOk == true ? "finished" : "failed") << "\r\n";

	initOk = DataInitialize();
	std::cout << _name << " Data setup " << (initOk == true ? "finished" : "failed") << "\r\n";
}

void FlightControlUnit::Manage()
{

}
