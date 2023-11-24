#pragma once
#include "ModuleMaster.h"
#include "SimController.h"
#include "ConsoleManager.h"
#include "CommManager.h"


class Program final
{
private:
	
	ConsoleManager consoleManager;
	SimController simController = SimController(consoleManager, nullptr);
	CommManager commManager = CommManager(consoleManager);

	ModuleMaster * moduleMaster;

	void Initialize();
	void Loop();

public:
	Program()
	{
		moduleMaster = new ModuleMaster(simController.GetSimServices(), consoleManager);
		simController.SetModuleMaster(moduleMaster);
	}

	void Run();

	~Program()
	{
		delete moduleMaster;
	}
};
