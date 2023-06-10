#pragma once

#include <windows.h>
#include "SimConnect.h"

class SimController
{
private:
	HANDLE hSimConnect = nullptr;
	bool _isConnected = false;

	bool TryConnect();
	void Disconnect();

public:

};

