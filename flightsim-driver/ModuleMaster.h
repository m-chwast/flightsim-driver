#pragma once

#include "ModuleBase.h"

class ModuleMaster : public ModuleBase
{
public:

	// Inherited via ModuleBase
	virtual bool Initialize() override;
	virtual bool Manage() override;
};

