#pragma once

#include <windows.h>
#include <thread>
#include "SimConnect.h"

class SimController
{
private:
	//thread that runs all controller logic
	std::thread* _controllerThread = nullptr;
	bool _stopSearchFlag = false;
	bool _startSearchFlag = false;
	bool _stopControllerFlag = false;

	HANDLE _hSimConnect = nullptr;
	bool _isConnected = false;

	//thread that runs only server search
	std::thread* _searchThread = nullptr;
	volatile bool _searchActive = false;

	void ControllerHandler();
	bool TryConnect();
	void Disconnect();
	void TryConnectPeriodically(unsigned period, bool connectOnce);

	void StartSearch(unsigned period, bool stopSearchAfterFirstConnection = false);
	void StopSearch();
public:
	SimController();

	void SearchForServer();
	void StopSearchForServer();

	~SimController();
};

