#pragma once

#include "ModuleHardware.h"
#include "StableButton.h"
#include <vector>

class FlightControlUnit final : public ModuleHardware
{
private:
	StableButton* _autothrustButton;
	StableButton* _autopilot1Button;
	StableButton* _autopilot2Button;
	StableButton* _expediteButton;
	StableButton* _locButton;
	StableButton* _apprButton;
	StableButton* _spdMachButton;
	StableButton* _trkFpaButton;

	std::vector<const Button*> _buttons;

	virtual bool EventsInitialize() override;
	virtual bool DataInitialize() override;
public:
	FlightControlUnit(const SimServices& simServices, ConsoleManager* console, unsigned id);

	virtual void ProcessData(const SIMCONNECT_RECV_SIMOBJECT_DATA* data) override;
	virtual void ProcessEvent(const SIMCONNECT_RECV_EVENT* event) override;

	~FlightControlUnit();
};

