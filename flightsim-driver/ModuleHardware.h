#pragma once
#include "ModuleBase.h"
#include "ControlDevice.h"
#include <vector>

class ModuleHardware : public ModuleBase
{
private:
	std::vector<ControlDevice> _devices;

public:
	ModuleHardware(const SimServices& simServices) : ModuleBase(simServices) {}

	virtual ~ModuleHardware() {}
};

