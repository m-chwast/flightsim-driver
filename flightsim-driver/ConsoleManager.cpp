#include "ConsoleManager.h"
#include <iostream>

using namespace std;

std::string ConsoleManager::GetCommand()
{
	string cmd = "";
	cin >> cmd;
	return cmd;
}

void ConsoleManager::operator()(bool& closeRequest)
{
	cout << "Console Manager running\r\n";

	while (closeRequest == false)
	{
		std::string command = GetCommand();

		if (command == "q" || command == "quit" || command == "exit")
		{
			closeRequest = true;
		}
		else
		{
			cout << "Unknown command\r\n";
		}
	}

	cout << "Exiting Console Manager...\r\n";
}
