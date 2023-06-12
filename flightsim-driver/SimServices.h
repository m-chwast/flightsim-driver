#pragma once

#include <windows.h>

class SimServices
{
private:
	HANDLE* _hSimConnect;

public:
	SimServices(HANDLE* hSimConnect) : _hSimConnect{ hSimConnect } {}

	bool SetUpSimEvent(unsigned moduleID, unsigned eventID, const char* simEventName) const;
	bool InvokeSimEvent(unsigned moduleID, unsigned eventID, DWORD eventData = 0) const;
};
