#pragma once

#include <string>
#include "ModuleUtils.h"


class ModuleBase
{
protected:
	std::string _name = "defaultName";
	const SimServices&  _simServices;
	ConsoleManager& _console;
	Comm::CommManager& _commManager;

	void PrintInitMessage();

public:
	ModuleBase(const ModuleUtils& utils)
		: _simServices{utils.GetSimServices()}, _console{utils.GetConsole()}, _commManager{utils.GetCommManager()}
	{}
	
	const char* GetName() const { return _name.c_str(); }

	virtual void Initialize() = 0;
	virtual void Manage() = 0;

	virtual ~ModuleBase() {}
};
