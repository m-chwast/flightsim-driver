#pragma once

#include <string>
#include "SimServices.h"
#include "ConsoleManager.h"
#include "ModuleUtils.h"


class ModuleBase
{
protected:
	std::string _name = "defaultName";
	const SimServices&  _simServices;
	ConsoleManager& _console;

	void PrintInitMessage();

public:
	ModuleBase(const ModuleUtils& utils)
		: _simServices{utils.GetSimServices()}, _console{utils.GetConsole()}
	{}
	
	const char* GetName() const { return _name.c_str(); }

	virtual void Initialize() = 0;
	virtual void Manage() = 0;

	virtual ~ModuleBase() {}
};
