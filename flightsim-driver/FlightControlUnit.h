#pragma once

#include "ModuleHardware.h"

class FlightControlUnit : public ModuleHardware
{
private:
	bool EventsInitialize();
public:
	FlightControlUnit(const SimServices& simServices, unsigned id);

	// Inherited via ModuleHardware
	virtual void Initialize() override;
	virtual void Manage() override;
};

