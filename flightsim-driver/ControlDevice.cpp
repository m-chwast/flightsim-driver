#include "ControlDevice.h"
#include <iostream>

void ControlDevice::EventHandler(int eventID, int data)
{
	std::cout << "Default event handler called for the device: " << _name << "\r\n";
}

void ControlDevice::DataHandler(const uint8_t* data)
{
	std::cout << "Default data handler called for the device: " << _name << "\r\n";
}
