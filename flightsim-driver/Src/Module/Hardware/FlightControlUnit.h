#pragma once
#include "ModuleHardware.h"
#include "StableButton.h"
#include "StableDataDrivenButton.h"
#include "PushPullEncoder.h"


class FlightControlUnit final : public ModuleHardware
{
private:
	typedef struct
	{
		struct LightedButtons
		{
			int32_t autopilotAutothrottleArm;
			int32_t autopilot1Active;
			int32_t autopilot2Active;
			int32_t expediteMode;
			int32_t locModeActive;
			int32_t apprModeActive;
		} lightedButtons;
		struct UnlightedButtons
		{
			int32_t spdMach;
			int32_t trkFpa;
			int32_t metricAlt;
		} unlightedButtons;
		struct Encoders
		{
			float spd;
			int32_t spdManagedDashes;
			int32_t spdManagedDot;
			int32_t hdg;
			int32_t hdgManagedDashes;
			int32_t hdgManagedDot;
			int32_t alt;
			int32_t altManaged;
			int32_t vs;
			float fpa;
			int32_t vsManaged;
		} encoders;
		struct Others
		{
			int32_t altInc;	//100 or 1000
		} others;
	} FCUData;

	static_assert(std::is_standard_layout<FCUData>::value, "FCUData is not-standard layout");
	static_assert(sizeof(float) == 4, "Bad float size");


	StableButton* _autothrustButton;
	StableButton* _autopilot1Button;
	StableButton* _autopilot2Button;
	StableButton* _expediteButton;
	StableButton* _locButton;
	StableButton* _apprButton;
	StableButton* _spdMachButton;
	StableButton* _trkFpaButton;
	StableDataDrivenButton* _metricAltButton;

	StableButton* _altIncrementSwitch;	//can be treated like a button, press should send 100 or 1000

	PushPullEncoder* _spdEncoder;
	PushPullEncoder* _hdgEncoder;
	PushPullEncoder* _altEncoder;
	PushPullEncoder* _vsEncoder;

	virtual bool DataInitialize() override;

	void RegisterFCUEvents();
	void CreateFCUButtons();
	void CreateFCUEncoders();

	void SendFCUDataToHardware(const FCUData& fcuData) const;

public:
	FlightControlUnit(const ModuleUtils& utils, unsigned id);

	virtual void ProcessData(const SIMCONNECT_RECV_SIMOBJECT_DATA* data) override;
	virtual void ProcessEvent(const SIMCONNECT_RECV_EVENT* event) override;

	~FlightControlUnit();
};

