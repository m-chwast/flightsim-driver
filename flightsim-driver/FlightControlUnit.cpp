#include <windows.h>
#include "FlightControlUnit.h"
#include <iostream>

typedef enum
{
	EVENT_AUTO_THROTTLE_ARM_TOGGLE,
} EventType;

typedef struct
{

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
	return false;
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
}

void FlightControlUnit::Manage()
{

}
