#include "Program.h"
#include <thread>
#include "ConsoleManager.h"

void Program::Initialize()
{

}

void Program::Loop()
{

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
