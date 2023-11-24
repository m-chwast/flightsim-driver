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

	void CommManager::SendData(unsigned moduleID, std::vector<uint8_t> data)
	{
		ModuleDataPacket* packet = new ModuleDataPacket();
		packet->header = COMM_PACKET_HEADER_STD_SKIP_CRC;
		packet->size = static_cast<uint16_t>(packet->GetBasicSize() + data.size());
		packet->type = COMM_PACKET_TYPE_MODULE_DATA;
		packet->crc = 0;		
		packet->moduleID = moduleID;
		packet->data = data;

		_packetsMutex.lock();
		_packetsToSend.push_back(packet);
		_packetsMutex.unlock();
	}

	CommManager::~CommManager()
	{
		_commManagerCloseRequest = true;
		_commManagerThread->join();
		std::cout << "Comm Manager thread joined\r\n";
		delete _commManagerThread;
	}
}
