#include "SimServices.h"
#include "SimConnect.h"
#include <iostream>

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
		std::cout << "Error while transmitting event. Module: ";
		std::cout << moduleID << ", Event: " << eventID << "\r\n";
		return false;
	}
	std::cout << "Transmitted event. Module: " << moduleID << ", Event: " << eventID << "\r\n";
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
