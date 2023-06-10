#include "ModuleBase.h"
#include <iostream>

void ModuleBase::PrintInitMessage()
{
	std::cout << "Initializing module: " << _name << "\r\n";
}
