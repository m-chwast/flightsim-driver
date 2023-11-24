#pragma once
#include <thread>
#include <vector>
#include "ConsoleManager.h"
#include "CommPackets.h"


namespace Comm
{

	class CommManager
	{
	private:
		ConsoleManager& _console;

		bool _commManagerCloseRequest = false;
		std::thread* _commManagerThread = nullptr;

		std::vector<const Packet*> _packetsToSend;

		void Handler(bool& closeRequest);

	public:
		CommManager(ConsoleManager& console)
			: _console{ console }
		{
			_commManagerThread = new std::thread(&CommManager::Handler, this, std::ref(_commManagerCloseRequest));
		}


		~CommManager();
	};

}
