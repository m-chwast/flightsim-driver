#include "Program.h"
#include <thread>
#include "ConsoleManager.h"

void Program::Initialize()
{
	simController.SearchForServer();
}

void Program::Loop()
{
	if (simController.IsConnected() == true)
	{
		moduleMaster->Manage();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Program::Run()
{
	bool closeRequest = false;
	//start console thread
	ConsoleManager consoleManager;
	std::thread consoleThread(&ConsoleManager::Handler, &consoleManager, std::ref(closeRequest));

	Initialize();

	while (closeRequest == false)
	{
		Loop();
	}

	consoleThread.join();
}
