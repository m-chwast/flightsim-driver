#pragma once

#include "ModuleBase.h"
#include "ModuleHardware.h"
#include <vector>

class ModuleMaster : public ModuleBase
{
private:
	
	std::vector<ModuleHardware*> _modules;

public:
	ModuleMaster();

	// Inherited via ModuleBase
	virtual void Initialize() override;
	virtual void Manage() override;
};
