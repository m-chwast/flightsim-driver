#pragma once

#include <vector>
#include <string>

class ControlDevice
{
private:
	unsigned _id;
	std::string _name;
	std::vector<std::string> _eventNames;
	std::vector<std::string> _dataNames;

public:
	ControlDevice(unsigned id, const char * name,
		std::vector<std::string> eventNames, std::vector<std::string> dataNames)
	{
		_id = id;
		_eventNames = eventNames;
		_dataNames = dataNames;
		_name = name;
	}

	/// <summary>
	/// called when any of the device's event is received
	/// </summary>
	virtual void EventHandler(int eventID, int data);
	
	/// <summary>
	/// called when data requested by the device is provided 
	/// </summary>
	virtual void DataHandler(const uint8_t * data);

	virtual ~ControlDevice() {}
};

