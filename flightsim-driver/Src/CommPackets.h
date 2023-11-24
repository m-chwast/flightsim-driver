#pragma once
#include <vector>

namespace Comm
{
	enum PacketHeader
	{
		COMM_PACKET_HEADER_STD,
	};

	enum PacketType
	{
		COMM_PACKET_TYPE_MODULE_DATA,
	};

	struct Packet
	{
		uint8_t header;
		uint16_t size;
		uint8_t type;
		uint32_t crc;
	};

	struct ModuleDataPacket : Packet
	{
		uint8_t moduleID;
	};
}
