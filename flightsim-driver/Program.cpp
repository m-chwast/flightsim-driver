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
	Sleep(1);
}

void Program::Run()
{
	bool closeRequest = false;
	//start console thread
	ConsoleManager consoleManager;
	std::thread consoleThread(consoleManager, std::ref(closeRequest));

	Initialize();

	while (closeRequest == false)
	{
		Loop();
	}

	consoleThread.join();
}
