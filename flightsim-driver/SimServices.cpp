#include "SimServices.h"

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
