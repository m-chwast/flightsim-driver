#include <windows.h>
#include <type_traits>
#include "FlightControlUnit.h"
#include "HardwareElementBase.h"


enum FCUEventType
{
	//buttons
	EVENT_AUTOTHRUST_PUSH,
	EVENT_AUTOPILOT_AP1_PUSH,
	EVENT_AUTOPILOT_AP2_PUSH,
	EVENT_EXPEDITE_PUSH,
	EVENT_LOC_PUSH,
	EVENT_APPR_PUSH,
	EVENT_SPD_MACH_TOGGLE_PUSH,
	EVENT_TRK_FPA_TOGGLE_PUSH,
	//encoders
	EVENT_SPD_INC,
	EVENT_SPD_DEC,
	EVENT_SPD_PUSH,
	EVENT_SPD_PULL,
	EVENT_HDG_INC,
	EVENT_HDG_DEC,
	EVENT_HDG_PUSH,
	EVENT_HDG_PULL,
	EVENT_ALT_INC,
	EVENT_ALT_DEC,
	EVENT_ALT_PUSH,
	EVENT_ALT_PULL,
	EVENT_VS_INC,
	EVENT_VS_DEC,
	EVENT_VS_PUSH,
	EVENT_VS_PULL,
	//others
	EVENT_ALT_INCREMENT_SET,
};

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
} FCUData;

static_assert(std::is_standard_layout<FCUData>::value, "FCUData is not-standard layout");

bool FlightControlUnit::DataInitialize()
{
	bool initOk = true;
	
	//data is initialized manually to provide better control on sequence
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_AUTOTHRUST_STATUS", "number", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_AUTOPILOT_1_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_AUTOPILOT_2_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FMA_EXPEDITE_MODE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FCU_LOC_MODE_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FCU_APPR_MODE_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "AUTOPILOT MANAGED SPEED IN MACH", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_TRK_FPA_MODE_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_METRIC_ALT_TOGGLE", "Boolean", SIMCONNECT_DATATYPE_INT32);

	return initOk;
}

void FlightControlUnit::RegisterFCUEvents()
{
	//buttons
	RegisterEvent(EVENT_AUTOTHRUST_PUSH, "AUTO_THROTTLE_ARM");
	RegisterEvent(EVENT_AUTOPILOT_AP1_PUSH, "A32NX.FCU_AP_1_PUSH");
	RegisterEvent(EVENT_AUTOPILOT_AP2_PUSH, "A32NX.FCU_AP_2_PUSH");
	RegisterEvent(EVENT_EXPEDITE_PUSH, "A32NX.FCU_EXPED_PUSH");
	RegisterEvent(EVENT_LOC_PUSH, "A32NX.FCU_LOC_PUSH");
	RegisterEvent(EVENT_APPR_PUSH, "A32NX.FCU_APPR_PUSH");
	RegisterEvent(EVENT_SPD_MACH_TOGGLE_PUSH, "A32NX.FCU_SPD_MACH_TOGGLE_PUSH");
	RegisterEvent(EVENT_TRK_FPA_TOGGLE_PUSH, "A32NX.FCU_TRK_FPA_TOGGLE_PUSH");
	//encoders
	RegisterEvent(EVENT_SPD_INC, "A32NX.FCU_SPD_INC");
	RegisterEvent(EVENT_SPD_DEC, "A32NX.FCU_SPD_DEC");
	RegisterEvent(EVENT_SPD_PUSH, "A32NX.FCU_SPD_PUSH");
	RegisterEvent(EVENT_SPD_PULL, "A32NX.FCU_SPD_PULL");
	RegisterEvent(EVENT_HDG_INC, "A32NX.FCU_HDG_INC");
	RegisterEvent(EVENT_HDG_DEC, "A32NX.FCU_HDG_DEC");
	RegisterEvent(EVENT_HDG_PUSH, "A32NX.FCU_HDG_PUSH");
	RegisterEvent(EVENT_HDG_PULL, "A32NX.FCU_HDG_PULL");
	RegisterEvent(EVENT_ALT_INC, "A32NX.FCU_ALT_INC");
	RegisterEvent(EVENT_ALT_DEC, "A32NX.FCU_ALT_DEC");
	RegisterEvent(EVENT_ALT_PUSH, "A32NX.FCU_ALT_PUSH");
	RegisterEvent(EVENT_ALT_PULL, "A32NX.FCU_ALT_PULL");
	RegisterEvent(EVENT_VS_INC, "A32NX.FCU_VS_INC"); 
	RegisterEvent(EVENT_VS_DEC, "A32NX.FCU_VS_DEC");
	RegisterEvent(EVENT_VS_PUSH, "A32NX.FCU_VS_PUSH");
	RegisterEvent(EVENT_VS_PULL, "A32NX.FCU_VS_PULL");
	//others
	RegisterEvent(EVENT_ALT_INCREMENT_SET, "A32NX.FCU_ALT_INCREMENT_SET");
}

void FlightControlUnit::CreateFCUButtons()
{
	HardwareElementBase base = HardwareElementBase(GetID(), DATA_REQUEST_ID_ACTION, _simServices, _console);

	/* "A32NX.FCU_ATHR_PUSH" event seems not to work, auto_throttle_arm works well though */
	_autothrustButton = new StableButton(base, GetEvent(EVENT_AUTOTHRUST_PUSH));
	RegisterButton(_autothrustButton);

	_autopilot1Button = new StableButton(base, GetEvent(EVENT_AUTOPILOT_AP1_PUSH));
	RegisterButton(_autopilot1Button);

	_autopilot2Button = new StableButton(base, GetEvent(EVENT_AUTOPILOT_AP2_PUSH));
	RegisterButton(_autopilot2Button);

	_expediteButton = new StableButton(base, GetEvent(EVENT_EXPEDITE_PUSH));
	RegisterButton(_expediteButton);

	_locButton = new StableButton(base, GetEvent(EVENT_LOC_PUSH));
	RegisterButton(_locButton);

	_apprButton = new StableButton(base, GetEvent(EVENT_APPR_PUSH));
	RegisterButton(_apprButton);

	_spdMachButton = new StableButton(base, GetEvent(EVENT_SPD_MACH_TOGGLE_PUSH));
	RegisterButton(_spdMachButton);

	_trkFpaButton = new StableButton(base, GetEvent(EVENT_TRK_FPA_TOGGLE_PUSH));
	RegisterButton(_trkFpaButton);

	_metricAltButton = new StableDataDrivenButton(base, (GetID() * 100) + 1, "L:A32NX_METRIC_ALT_TOGGLE");
	RegisterButton(_metricAltButton);
}

void FlightControlUnit::CreateFCUEncoders()
{

}

FlightControlUnit::FlightControlUnit(const SimServices& simServices, ConsoleManager& console, unsigned id)
	: ModuleHardware(simServices, console, id)
{
	_name = "FCU";
	_dataUpdatePeriod = 1000;

	RegisterFCUEvents();

	CreateFCUButtons();
	CreateFCUEncoders();
}

void FlightControlUnit::ProcessData(const SIMCONNECT_RECV_SIMOBJECT_DATA* data)
{
	_console.Send(_name + " Module Data Processing: ");
	
	if (data == nullptr)
	{
		_console.Send(" error!\r\n");
		return;
	}

	const FCUData* fcuData = reinterpret_cast<const FCUData*>(&data->dwData);

	_autothrustButton->SetState(fcuData->lightedButtons.autopilotAutothrottleArm);
	_autopilot1Button->SetState(fcuData->lightedButtons.autopilot1Active);
	_autopilot2Button->SetState(fcuData->lightedButtons.autopilot2Active);
	_expediteButton->SetState(fcuData->lightedButtons.expediteMode);
	_locButton->SetState(fcuData->lightedButtons.locModeActive);
	_apprButton->SetState(fcuData->lightedButtons.apprModeActive);
	_spdMachButton->SetState(fcuData->unlightedButtons.spdMach);
	_trkFpaButton->SetState(fcuData->unlightedButtons.trkFpa);
	_metricAltButton->SetState(fcuData->unlightedButtons.metricAlt);

	_console.Send("A/THR: " + std::to_string(_autothrustButton->IsActive()) + "\r\n");
	_console.Send("AP1: " + std::to_string(_autopilot1Button->IsActive()) + "\r\n");
	_console.Send("AP2: " + std::to_string(_autopilot2Button->IsActive()) + "\r\n");
	_console.Send("EXPED: " + std::to_string(_expediteButton->IsActive()) + "\r\n");
	_console.Send("LOC: " + std::to_string(_locButton->IsActive()) + "\r\n");
	_console.Send("APPR: " + std::to_string(_apprButton->IsActive()) + "\r\n");
	_console.Send("SPD/MACH: " + std::to_string(_spdMachButton->IsActive()) + "\r\n");
	_console.Send("TRK/FPA: " + std::to_string(_trkFpaButton->IsActive()) + "\r\n");
	_console.Send("Metric Alt: " + std::to_string(_metricAltButton->IsActive()) + "\r\n");
	_console.Send("\r\n");
}

void FlightControlUnit::ProcessEvent(const SIMCONNECT_RECV_EVENT* event)
{

}

FlightControlUnit::~FlightControlUnit()
{
	delete _autothrustButton;
	delete _autopilot1Button;
	delete _autopilot2Button;
	delete _expediteButton;
	delete _locButton;
	delete _apprButton;
	delete _spdMachButton;
	delete _trkFpaButton;
}
