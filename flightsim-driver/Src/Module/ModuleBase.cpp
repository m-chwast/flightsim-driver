#include "ModuleBase.h"

void ModuleBase::PrintInitMessage()
{
	_console.Send("Initializing module: " + _name + "\r\n");
}
