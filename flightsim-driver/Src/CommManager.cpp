#include "CommManager.h"
#include <iostream>


namespace Comm
{

	void CommManager::Handler(bool& closeRequest)
	{
		_console.Send("Comm Manager running\r\n");

		while (closeRequest == false)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}

		_console.Send("Exiting Comm Manager\r\n");
	}

	CommManager::~CommManager()
	{
		_commManagerCloseRequest = true;
		_commManagerThread->join();
		std::cout << "Comm Manager thread joined\r\n";
		delete _commManagerThread;
	}

}
