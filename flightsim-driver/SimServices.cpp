#include "SimServices.h"
#include "SimConnect.h"

bool SimServices::SetUpSimEvent(unsigned moduleID, unsigned eventID, const char* simEventName) const
{
	HRESULT result;
	
	result = SimConnect_MapClientEventToSimEvent(*_hSimConnect, eventID, simEventName);
	if (result != S_OK)
	{
		return false;
	}

	result = SimConnect_AddClientEventToNotificationGroup(*_hSimConnect, moduleID, eventID);
	if (result != S_OK)
	{
		return false;
	}
	return true;
}

bool SimServices::InvokeSimEvent(unsigned moduleID, unsigned eventID, DWORD eventData) const
{
	HRESULT res = SimConnect_TransmitClientEvent(*_hSimConnect, SIMCONNECT_OBJECT_ID_USER,
		eventID, eventData, moduleID, SIMCONNECT_EVENT_FLAG_DEFAULT);

	if (res != S_OK)
	{
		std::string msg = "Error while transmitting event. Module: " + std::to_string(moduleID);
		msg += ", Event: " + std::to_string(eventID) + "\r\n";
		_console->Send(msg);
		return false;
	}
	std::string msg = "Transmitted event. Module: " + std::to_string(moduleID);
	msg += ", Event: " + std::to_string(eventID) + "\r\n";
	_console->Send(msg);
	return true;
}

bool SimServices::SetUpData(unsigned moduleID, const char* dataName, const char* unitsName, SIMCONNECT_DATATYPE dataType) const
{
	HRESULT res = SimConnect_AddToDataDefinition(*_hSimConnect, moduleID, dataName, unitsName, dataType);
	
	if (res != S_OK)
	{
		return false;
	}
	return true;
}

bool SimServices::RequestData(unsigned moduleID, int requestID) const
{
	HRESULT res = SimConnect_RequestDataOnSimObject(*_hSimConnect, requestID, moduleID,
		SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);

	if (res != S_OK)
	{
		_console->Send("Error while requesting data. Module: " + std::to_string(moduleID) + "\r\n");
		return false;
	}
	_console->Send("Requested data. Module: " + std::to_string(moduleID) + "\r\n");
	return true;
}
