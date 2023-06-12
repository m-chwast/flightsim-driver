#pragma once

#include "ModuleHardware.h"

class FlightControlUnit : public ModuleHardware
{
private:

public:
	FlightControlUnit();

	// Inherited via ModuleHardware
	virtual void Initialize() override;
	virtual void Manage() override;
};

