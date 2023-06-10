#pragma once

#include <windows.h>
#include <thread>
#include "SimConnect.h"

class SimController
{
private:
	//thread that runs all controller logic
	std::thread* controllerThread = nullptr;

	HANDLE hSimConnect = nullptr;
	bool _isConnected = false;

	//thread that runs only server search
	std::thread* _searchThread = nullptr;
	volatile bool _searchActive = false;

	bool TryConnect();
	void Disconnect();
	void TryConnectPeriodically(unsigned period, bool connectOnce);

public:
	void SearchForServer(unsigned period, bool stopSearchAfterFirstConnection = false);
	void StopSearch();
};

