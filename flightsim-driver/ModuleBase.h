#pragma once

#include <string>
#include "SimServices.h"

class ModuleBase
{
protected:
	std::string _name = "defaultName";
	const SimServices * _simServices;

	void PrintInitMessage();

public:
	ModuleBase(const SimServices& simServices)
	{
		_simServices = &simServices;
	}
	
	const char* GetName() const { return _name.c_str(); }

	virtual void Initialize() = 0;
	virtual void Manage() = 0;

	virtual ~ModuleBase() {}
};
