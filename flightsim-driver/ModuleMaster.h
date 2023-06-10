#pragma once

#include "ModuleBase.h"
#include <vector>

class ModuleMaster : public ModuleBase
{
private:
	
	std::vector<ModuleBase> _modules;

public:

	// Inherited via ModuleBase
	virtual void Initialize() override;
	virtual void Manage() override;
};
