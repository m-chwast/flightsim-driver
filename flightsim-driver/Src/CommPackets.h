#pragma once
#include <vector>

namespace Comm
{
	enum PacketHeader
	{
		COMM_PACKET_HEADER_STD,
		COMM_PACKET_HEADER_STD_SKIP_CRC,
	};

	enum PacketType
	{
		COMM_PACKET_TYPE_MODULE_DATA,
	};

	struct Packet
	{
		uint8_t header = 0;
		uint16_t size = 0;
		uint8_t type = 0;
		uint32_t crc = 0;

		virtual constexpr uint16_t GetBasicSize() const { return sizeof(header) + sizeof(size) + sizeof(type) + sizeof(crc); }

		virtual std::vector<uint8_t> GetData() const
		{
			return std::vector<uint8_t>({ 
				header, 
				static_cast<uint8_t>(size >> 8), static_cast<uint8_t>(size),
				type,
				static_cast<uint8_t>(crc >> 24), static_cast<uint8_t>(crc >> 16), 
				static_cast<uint8_t>(crc >> 8), static_cast<uint8_t>(crc) });
		}
	};

	struct ModuleDataPacket : Packet
	{
		uint8_t moduleID = 0;

		std::vector<uint8_t> data;

		virtual constexpr uint16_t GetBasicSize() const override { return sizeof(moduleID) + Packet::GetBasicSize(); }

		virtual std::vector<uint8_t> GetData() const override
		{
			std::vector<uint8_t> rawData = Packet::GetData();
			rawData.reserve(GetBasicSize() + data.size());

			rawData.push_back(moduleID);
			for (uint8_t val : data)
			{
				rawData.push_back(val);
			}
			return rawData;
		}
	};
}
