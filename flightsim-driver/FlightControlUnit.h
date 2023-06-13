#pragma once

#include "ModuleHardware.h"

class FlightControlUnit final : public ModuleHardware
{
private:
	bool _autoThrottleArmed = false;

	void AutoThrottleButtonPressed() const;

	virtual bool EventsInitialize() override;
	virtual bool DataInitialize() override;
public:
	FlightControlUnit(const SimServices& simServices, unsigned id);

	virtual void ProcessData(const SIMCONNECT_RECV_SIMOBJECT_DATA* data) override;

	virtual void Manage() override;
};

