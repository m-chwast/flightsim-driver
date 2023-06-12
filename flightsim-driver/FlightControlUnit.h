#pragma once

#include "ModuleHardware.h"

class FlightControlUnit : public ModuleHardware
{
private:

public:
	FlightControlUnit(const SimServices& simServices);

	// Inherited via ModuleHardware
	virtual void Initialize() override;
	virtual void Manage() override;
};

