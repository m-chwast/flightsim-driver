#pragma once

#include "ModuleHardware.h"

class FlightControlUnit final : public ModuleHardware
{
private:
	bool _autoThrottleArmed = false;

	virtual bool EventsInitialize() override;
	virtual bool DataInitialize() override;
public:
	FlightControlUnit(const SimServices& simServices, unsigned id);

	virtual void Manage() override;
};

