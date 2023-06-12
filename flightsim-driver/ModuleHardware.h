#pragma once
#include "ModuleBase.h"
#include "ControlDevice.h"
#include <vector>

class ModuleHardware : public ModuleBase
{
private:
	std::vector<ControlDevice> _devices;

	unsigned _id;

public:
	ModuleHardware(const SimServices& simServices, unsigned id) : ModuleBase(simServices)
	{
		_id = id;
	}

	unsigned GetID() const { return _id; }

	virtual ~ModuleHardware() {}
};

