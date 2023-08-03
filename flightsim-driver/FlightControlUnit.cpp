#include <windows.h>
#include "FlightControlUnit.h"

typedef enum
{
	EVENT_AUTO_THROTTLE_ARM_TOGGLE,
	EVENT_AUTOPILOT_AP1_PUSH,
	EVENT_AUTOPILOT_AP2_PUSH,
} EventType;

typedef struct
{
	int32_t autopilotAutothrottleArm;
	int32_t autopilot1Active;
	int32_t autopilot2Active;
} FCUData;


bool FlightControlUnit::EventsInitialize()
{
	bool initOk = true;
	
	for(const Button * b : _buttons)
	{
		bool eventSetupOk = b->EventSetup();
		if (eventSetupOk == false)
			initOk = false;
	}

	return initOk;
}

bool FlightControlUnit::DataInitialize()
{
	bool initOk = true;
	
	//data must be initialized manually to provide better control on sequence
	bool tmpOk = _simServices->SetUpData(GetID(), "AUTOPILOT THROTTLE ARM", "Boolean", SIMCONNECT_DATATYPE_INT32);
	if (tmpOk != true)
		initOk = false;

	tmpOk = _simServices->SetUpData(GetID(), "L:A32NX_AUTOPILOT_1_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	if (tmpOk != true)
		initOk = false;

	tmpOk = _simServices->SetUpData(GetID(), "L:A32NX_AUTOPILOT_2_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	if (tmpOk != true)
		initOk = false;

	return initOk;
}

FlightControlUnit::FlightControlUnit(const SimServices& simServices, ConsoleManager* console, unsigned id)
	: ModuleHardware(simServices, console, id)
{
	_name = "FCU";
	_dataUpdatePeriod = 1000;

	constexpr unsigned dataRequestID = DATA_REQUEST_ID_ACTION;

	_autothrustButton = new StableButton(GetID(), EVENT_AUTO_THROTTLE_ARM_TOGGLE, "AUTO_THROTTLE_ARM", DATA_REQUEST_ID_ACTION, &simServices, console);
	_buttons.push_back(_autothrustButton);

	_autopilot1Button = new StableButton(GetID(), EVENT_AUTOPILOT_AP1_PUSH, "A32NX.FCU_AP_1_PUSH", dataRequestID, &simServices, console);
	_buttons.push_back(_autopilot1Button);

	_autopilot2Button = new StableButton(GetID(), EVENT_AUTOPILOT_AP2_PUSH, "A32NX.FCU_AP_2_PUSH", dataRequestID, &simServices, console);
	_buttons.push_back(_autopilot2Button);
}

void FlightControlUnit::ProcessData(const SIMCONNECT_RECV_SIMOBJECT_DATA* data)
{
	_console->Send(_name + " Module Data Processing: ");
	
	if (data == nullptr)
	{
		_console->Send(" error!\r\n");
		return;
	}

	const FCUData* fcuData = reinterpret_cast<const FCUData*>(&data->dwData);

	_autothrustButton->SetState(fcuData->autopilotAutothrottleArm);
	_autopilot1Button->SetState(fcuData->autopilot1Active);
	_autopilot2Button->SetState(fcuData->autopilot2Active);

	_console->Send("A/THR: " + std::to_string(_autothrustButton->IsActive()) + "\r\n");
	_console->Send("AP1: " + std::to_string(_autopilot1Button->IsActive()) + "\r\n");
	_console->Send("AP2: " + std::to_string(_autopilot2Button->IsActive()) + "\r\n");
	_console->Send("\r\n");
}

FlightControlUnit::~FlightControlUnit()
{
	delete _autothrustButton;
	delete _autopilot1Button;
	delete _autopilot2Button;
}
