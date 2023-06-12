#pragma once

#include <windows.h>
#include "SimConnect.h"

class SimServices
{
private:
	HANDLE* _hSimConnect;

public:
	SimServices(HANDLE* hSimConnect) : _hSimConnect{ hSimConnect } {}

	bool SetUpSimEvent(unsigned moduleID, unsigned eventID, const char* simEventName) const;
	bool InvokeSimEvent(unsigned moduleID, unsigned eventID, DWORD eventData = 0) const;

	bool SetUpData(unsigned moduleID, const char* dataName, const char* unitsName, 
		SIMCONNECT_DATATYPE dataType = SIMCONNECT_DATATYPE_FLOAT64) const;
	bool RequestData(unsigned moduleID, int requestID = 0) const;
};
