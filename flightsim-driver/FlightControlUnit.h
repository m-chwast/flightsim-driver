#pragma once

#include "ModuleHardware.h"

class FlightControlUnit : public ModuleHardware
{
private:
	bool _autoThrottleArmed = false;

	bool EventsInitialize();
	bool DataInitialize();
public:
	FlightControlUnit(const SimServices& simServices, unsigned id);

	// Inherited via ModuleHardware
	virtual void Initialize() override;
	virtual void Manage() override;
};

