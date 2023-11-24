#pragma once
#include "ModuleMaster.h"
#include "SimController.h"
#include "ConsoleManager.h"
#include "CommManager.h"
#include "ModuleUtils.h"


class Program final
{
private:
	
	ConsoleManager consoleManager;
	SimController simController = SimController(consoleManager, nullptr);
	Comm::CommManager commManager = Comm::CommManager(consoleManager);

	ModuleMaster * moduleMaster;

	void Initialize();
	void Loop();

public:
	Program()
	{
		ModuleUtils utils = ModuleUtils(simController.GetSimServices(), consoleManager, commManager);
		moduleMaster = new ModuleMaster(utils);
		simController.SetModuleMaster(moduleMaster);
	}

	void Run();

	~Program()
	{
		delete moduleMaster;
	}
};
