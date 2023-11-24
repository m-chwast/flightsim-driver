#pragma once
#include "SimServices.h"
#include "ConsoleManager.h"
#include "CommManager.h"


class ModuleUtils final
{
private:
	const SimServices& _simServices;
	ConsoleManager& _console;
	Comm::CommManager& _commManager;

public:
	ModuleUtils(const SimServices& simServices, ConsoleManager& console, Comm::CommManager& commManager)
		: _simServices{ simServices }, _console{ console }, _commManager{ commManager }
	{}
	
	const SimServices& GetSimServices() const { return _simServices; }
	ConsoleManager& GetConsole() const { return _console; }
	Comm::CommManager& GetCommManager() const { return _commManager; }
};
