#include "ConsoleManager.h"
#include <iostream>
#include <thread>


std::string ConsoleManager::GetCommand()
{
	std::string cmd = "";
	std::cin >> cmd;
	return cmd;
}

void ConsoleManager::Writer(bool* closeRequest)
{
	std::cout << "Console Writer running\r\n";

	while (*closeRequest == false) 
	{
		
		_messagesMutex.lock();
		for (const std::string & s : _messages)
		{
			std::cout << s;
		}
		_messages.clear();
		_messagesMutex.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	
	std::cout << "Closing Console Writer\r\n";
}

void ConsoleManager::Handler(bool& closeRequest)
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
			Send("Unknown command\r\n");
		}
	}

	writerThread.join();
	std::cout << "Exiting Console Manager...\r\n";
}

void ConsoleManager::Send(std::string message, int priority)
{
	_messagesMutex.lock();
	_messages.push_back(std::move(message));
	_messagesMutex.unlock();
}
