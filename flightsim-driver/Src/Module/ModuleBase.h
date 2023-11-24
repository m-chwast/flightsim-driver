#pragma once

#include <string>
#include "SimServices.h"
#include "ConsoleManager.h"

class ModuleBase
{
protected:
	std::string _name = "defaultName";
	const SimServices&  _simServices;
	ConsoleManager& _console;

	void PrintInitMessage();

public:
	ModuleBase(const SimServices& simServices, ConsoleManager& console)
		: _simServices{simServices}, _console{console}
	{}
	
	const char* GetName() const { return _name.c_str(); }

	virtual void Initialize() = 0;
	virtual void Manage() = 0;

	virtual ~ModuleBase() {}
};
