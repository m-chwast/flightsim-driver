#pragma once

#include <windows.h>
#include "SimConnect.h"
#include "ConsoleManager.h"

class SimServices
{
private:
	HANDLE* _hSimConnect;

	ConsoleManager& _console;

public:
	SimServices(HANDLE* hSimConnect, ConsoleManager& console) : _hSimConnect{ hSimConnect }, _console{ console } {}

	bool SetUpSimEvent(unsigned moduleID, unsigned eventID, const char* simEventName) const;
	bool InvokeSimEvent(unsigned moduleID, unsigned eventID, DWORD eventData = 0) const;
	bool SetModuleEventsPriority(unsigned moduleID, DWORD priority) const;

	bool SetUpData(unsigned moduleID, const char* dataName, const char* unitsName, 
		SIMCONNECT_DATATYPE dataType = SIMCONNECT_DATATYPE_FLOAT64) const;
	bool RequestData(unsigned moduleID, int requestID = 0) const;
	bool SetData(unsigned moduleID, unsigned elemCount, unsigned elemSize, void* data) const;
};
