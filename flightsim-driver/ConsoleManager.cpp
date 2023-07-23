#include "ConsoleManager.h"
#include <iostream>
#include <thread>


std::string ConsoleManager::GetCommand()
{
	std::string cmd = "";
	std::cin >> cmd;
	return cmd;
}

void ConsoleManager::Writer(bool* closeRequest) const
{
	std::cout << "Console Writer running\r\n";

	while (*closeRequest == false) 
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	 
	std::cout << "Closing Console Writer\r\n";
}

void ConsoleManager::operator()(bool& closeRequest)
{
	std::cout << "Console Manager running\r\n";

	std::thread writerThread(&ConsoleManager::Writer, this, &closeRequest);

	while (closeRequest == false)
	{
		std::string command = GetCommand();

		if (command == "q" || command == "quit" || command == "exit")
		{
			closeRequest = true;
		}
		else
		{
			std::cout << "Unknown command\r\n";
		}
	}

	writerThread.join();
	std::cout << "Exiting Console Manager...\r\n";
}
