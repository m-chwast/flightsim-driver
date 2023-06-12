#pragma once

#include "ModuleMaster.h"
#include "SimController.h"

class Program final
{
private:
	
	SimController simController;
	ModuleMaster * moduleMaster;

	void Initialize();
	void Loop();

public:
	Program()
	{
		moduleMaster = new ModuleMaster(simController.GetSimServices());
	}

	void Run();

	~Program()
	{
		delete moduleMaster;
	}
};
