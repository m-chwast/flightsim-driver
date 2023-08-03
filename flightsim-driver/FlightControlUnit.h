#pragma once

#include "ModuleHardware.h"
#include "StableButton.h"

class FlightControlUnit final : public ModuleHardware
{
private:
	StableButton* _autoThrottleButton;
	
	void AutoThrottleButtonPressed() const;

	virtual bool EventsInitialize() override;
	virtual bool DataInitialize() override;
public:
	FlightControlUnit(const SimServices& simServices, ConsoleManager* console, unsigned id);

	virtual void ProcessData(const SIMCONNECT_RECV_SIMOBJECT_DATA* data) override;

	~FlightControlUnit();
};

