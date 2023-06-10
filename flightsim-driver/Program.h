#pragma once

#include "ModuleMaster.h"

class Program final
{
private:
	
	ModuleMaster moduleMaster;

	void Initialize();
	void Loop();

public:

	void Run();
};
