#pragma once
#include <Windows.h>
#include "SimConnect.h"

class SimServices
{
private:
	HANDLE* _hSimConnect;

public:
	SimServices(HANDLE* hSimConnect) : _hSimConnect{ hSimConnect } {}

	bool SetUpSimEvent(unsigned moduleID, unsigned eventID, const char * simEventName) const;
};
