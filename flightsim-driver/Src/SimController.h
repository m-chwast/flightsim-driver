#pragma once

#include <windows.h>
#include <thread>
#include "SimConnect.h"
#include "SimServices.h"
#include "ModuleMaster.h"
#include "ConsoleManager.h"

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

	SimServices * _simServices;
	const ModuleMaster* _moduleMaster;
	ConsoleManager& _console;

	void ControllerHandler();
	bool TryConnect();
	void Disconnect();
	void TryConnectPeriodically(unsigned period, bool connectOnce);

	void StartSearch(unsigned period, bool stopSearchAfterFirstConnection = false);
	void StopSearch();

	void DispatchHandler();
	void DispatchHandlerProcessData(const SIMCONNECT_RECV* data);

public:
	//ModuleMaster needs to be provided for event and data handling
	SimController(ConsoleManager& console, const ModuleMaster* moduleMaster = nullptr);

	void SearchForServer();
	void StopSearchForServer();

	bool IsConnected() { return _isConnected; }

	const SimServices& GetSimServices() const { return *_simServices; }

	void SetModuleMaster(ModuleMaster* moduleMaster) { _moduleMaster = moduleMaster; }

	~SimController();
};

