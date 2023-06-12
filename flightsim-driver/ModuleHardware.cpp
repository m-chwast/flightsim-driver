#include "ModuleHardware.h"
#include <iostream>

void ModuleHardware::Initialize()
{
	PrintInitMessage();

	bool initOk = EventsInitialize();
	std::cout << _name << " Event setup " << (initOk == true ? "finished" : "failed") << "\r\n";

	initOk = DataInitialize();
	std::cout << _name << " Data setup " << (initOk == true ? "finished" : "failed") << "\r\n";
}
