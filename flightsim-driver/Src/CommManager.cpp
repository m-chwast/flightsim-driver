#include <thread>
#include "CommManager.h"


void CommManager::Handler(bool& closeRequest)
{
	_console.Send("Comm Manager running\r\n");

	while (closeRequest == false)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}

	_console.Send("Exiting Comm Manager\r\n");
}
