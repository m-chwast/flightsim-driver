#include "ConsoleManager.h"
#include <iostream>
#include <thread>


std::string ConsoleManager::GetCommand()
{
	std::string cmd = "";
	std::cin >> cmd;
	return cmd;
}

void ConsoleManager::Writer(const bool& closeRequest)
{

}

void ConsoleManager::operator()(bool& closeRequest)
{
	std::cout << "Console Manager running\r\n";

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

	std::cout << "Exiting Console Manager...\r\n";
}
