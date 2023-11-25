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

typedef struct
{
	//indicators/buttons
	uint8_t autothrottle : 1;
	uint8_t autopilot1 : 1;
	uint8_t autopilot2 : 1;
	uint8_t expedite : 1;
	uint8_t loc : 1;
	uint8_t appr : 1;
	//flags/modes
	uint8_t spdMach : 1;
	uint8_t fpaActive : 1;
	uint8_t spdDashes : 1;
	uint8_t spdDot : 1;
	uint8_t hdgDashes : 1;
	uint8_t hdgDot : 1;
	uint8_t altManaged : 1;
	uint8_t vsManaged : 1;
	uint8_t altInc : 1;
	//values
	uint16_t spd;
	uint16_t hdg;
	uint16_t alt;
	uint16_t vsFpa;
} HardwareData;


static_assert(std::is_standard_layout<FCUData>::value, "FCUData is not-standard layout");
static_assert(sizeof(float) == 4, "Bad float size");


bool FlightControlUnit::DataInitialize()
{
	bool initOk = true;
	
	//data is initialized manually to provide better control on sequence
	//lightedButtons
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_AUTOTHRUST_STATUS", "Number", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_AUTOPILOT_1_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_AUTOPILOT_2_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FMA_EXPEDITE_MODE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FCU_LOC_MODE_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FCU_APPR_MODE_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	//unlightedButtons
	initOk &= _simServices.SetUpData(GetID(), "AUTOPILOT MANAGED SPEED IN MACH", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_TRK_FPA_MODE_ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_METRIC_ALT_TOGGLE", "Boolean", SIMCONNECT_DATATYPE_INT32);
	//encoders
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_AUTOPILOT_SPEED_SELECTED", "Number", SIMCONNECT_DATATYPE_FLOAT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FCU_SPD_MANAGED_DASHES", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FCU_SPD_MANAGED_DOT", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_AUTOPILOT_HEADING_SELECTED", "Degrees", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FCU_HDG_MANAGED_DASHES", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FCU_HDG_MANAGED_DOT", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "AUTOPILOT ALTITUDE LOCK VAR:3", "Feet", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FCU_ALT_MANAGED", "Boolean", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_AUTOPILOT_VS_SELECTED", "Feet/minute", SIMCONNECT_DATATYPE_INT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_AUTOPILOT_FPA_SELECTED", "Degrees", SIMCONNECT_DATATYPE_FLOAT32);
	initOk &= _simServices.SetUpData(GetID(), "L:A32NX_FCU_VS_MANAGED", "Boolean", SIMCONNECT_DATATYPE_INT32);
	//others
	initOk &= _simServices.SetUpData(GetID(), "L:XMLVAR_AUTOPILOT_ALTITUDE_INCREMENT", "Number", SIMCONNECT_DATATYPE_INT32);
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

	_metricAltButton = new StableDataDrivenButton(base, GetFirstReservedID() + 1, "L:A32NX_METRIC_ALT_TOGGLE");
	RegisterButton(_metricAltButton);

	_altIncrementSwitch = new StableButton(base, GetEvent(EVENT_ALT_INCREMENT_SET));
	RegisterButton(_altIncrementSwitch);
}

void FlightControlUnit::CreateFCUEncoders()
{
	HardwareElementBase base = HardwareElementBase(GetID(), DATA_REQUEST_ID_ACTION, _simServices, _console);
	
	_spdEncoder = new PushPullEncoder(base, GetEvent(EVENT_SPD_INC), GetEvent(EVENT_SPD_DEC), GetEvent(EVENT_SPD_PUSH), GetEvent(EVENT_SPD_PULL));
	RegisterEncoder(_spdEncoder);

	_hdgEncoder = new PushPullEncoder(base, GetEvent(EVENT_HDG_INC), GetEvent(EVENT_HDG_DEC), GetEvent(EVENT_HDG_PUSH), GetEvent(EVENT_HDG_PULL));
	RegisterEncoder(_hdgEncoder);
	
	_altEncoder = new PushPullEncoder(base, GetEvent(EVENT_ALT_INC), GetEvent(EVENT_ALT_DEC), GetEvent(EVENT_ALT_PUSH), GetEvent(EVENT_ALT_PULL));
	RegisterEncoder(_altEncoder);

	_vsEncoder = new PushPullEncoder(base, GetEvent(EVENT_VS_INC), GetEvent(EVENT_VS_DEC), GetEvent(EVENT_VS_PUSH), GetEvent(EVENT_VS_PULL));
	RegisterEncoder(_vsEncoder);
}

FlightControlUnit::FlightControlUnit(const ModuleUtils& utils, unsigned id)
	: ModuleHardware(utils, id)
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
	_altIncrementSwitch->SetState(fcuData->others.altInc == 1000);

	std::string log(1000, '\0');
	log = "\r\n";
	log += "A/THR: " + std::to_string(_autothrustButton->IsActive()) + "; ";
	log += "AP1: " + std::to_string(_autopilot1Button->IsActive()) + "; ";
	log += "AP2: " + std::to_string(_autopilot2Button->IsActive()) + "; ";
	log += "EXPED: " + std::to_string(_expediteButton->IsActive()) + "; ";
	log += "LOC: " + std::to_string(_locButton->IsActive()) + "; ";
	log += "APPR: " + std::to_string(_apprButton->IsActive()) + ";\r\n";
	log += "SPD/MACH: " + std::to_string(_spdMachButton->IsActive()) + "; ";
	log += "TRK/FPA: " + std::to_string(_trkFpaButton->IsActive()) + "; ";
	log += "Metric Alt: " + std::to_string(_metricAltButton->IsActive()) + "; ";
	log += "Alt Inc: " + std::to_string(_altIncrementSwitch->IsActive() ? 1000 : 100) + ";\r\n";

	log += "Spd sel: " + std::to_string(fcuData->encoders.spd) + "; ";
	log += "Spd dashes: " + std::to_string(fcuData->encoders.spdManagedDashes) + "; ";
	log += "Spd dot: " + std::to_string(fcuData->encoders.spdManagedDot) + ";\r\n";
	
	log += "Hdg sel: " + std::to_string(fcuData->encoders.hdg) + "; ";
	log += "Hdg dashes: " + std::to_string(fcuData->encoders.hdgManagedDashes) + "; ";
	log += "Hdg dot: " + std::to_string(fcuData->encoders.hdgManagedDot) + ";\r\n";

	log += "Alt sel: " + std::to_string(fcuData->encoders.alt) + "; ";
	log += "Alt dot: " + std::to_string(fcuData->encoders.altManaged) + "; ";
	log += "FPA sel: " + std::to_string(fcuData->encoders.fpa) + "; ";
	log += "VS sel: " + std::to_string(fcuData->encoders.vs) + "; ";
	log += "VS dashes: " + std::to_string(fcuData->encoders.vsManaged) + ";\r\n";
	
	log += "\r\n";
	_console.Send(log);
}

void FlightControlUnit::ProcessEvent(const SIMCONNECT_RECV_EVENT* event)
{

}

FlightControlUnit::~FlightControlUnit()
{

}
