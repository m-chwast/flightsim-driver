#pragma once

#include "ModuleBase.h"
#include "ModuleHardware.h"
#include <vector>

class ModuleMaster : public ModuleBase
{
private:
	bool _initialized = false;

	std::vector<ModuleHardware*> _modules;

public:
	ModuleMaster(const SimServices& simServices);

	// Inherited via ModuleBase
	virtual void Initialize() override;
	virtual void Manage() override;

	ModuleHardware* GetModule(unsigned long moduleID) const;
};
