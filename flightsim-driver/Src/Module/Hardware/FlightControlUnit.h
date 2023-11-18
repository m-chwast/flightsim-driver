#pragma once
#include "ModuleHardware.h"
#include "StableButton.h"
#include "StableDataDrivenButton.h"
#include "PushPullEncoder.h"


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
	StableDataDrivenButton* _metricAltButton;

	PushPullEncoder* _spdEncoder;
	PushPullEncoder* _hdgEncoder;
	PushPullEncoder* _altEncoder;
	PushPullEncoder* _vsEncoder;

	virtual bool DataInitialize() override;

	void RegisterFCUEvents();

public:
	FlightControlUnit(const SimServices& simServices, ConsoleManager& console, unsigned id);

	virtual void ProcessData(const SIMCONNECT_RECV_SIMOBJECT_DATA* data) override;
	virtual void ProcessEvent(const SIMCONNECT_RECV_EVENT* event) override;

	~FlightControlUnit();
};

