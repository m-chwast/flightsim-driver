#pragma once
#include <thread>
#include <vector>
#include <mutex>
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

		std::mutex _packetsMutex;
		std::vector<const Packet*> _packetsToSend;

		void Handler(bool& closeRequest);

	public:
		CommManager(ConsoleManager& console)
			: _console{ console }
		{
			_commManagerThread = new std::thread(&CommManager::Handler, this, std::ref(_commManagerCloseRequest));
		}

		void SendData(unsigned moduleID, std::vector<uint8_t> data);

		~CommManager();
	};

}
