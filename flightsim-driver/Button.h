#pragma once

#include "ControlDevice.h"

class Button : public ControlDevice
{
private:

public:
	Button(unsigned id, const char * name, std::string clickEventName, std::string dataName = "")
		: ControlDevice(id, name, { clickEventName }, { dataName })
	{
		
	}
};

