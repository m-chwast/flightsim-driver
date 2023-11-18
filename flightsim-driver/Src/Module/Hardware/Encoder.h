#pragma once
#include <string>
#include <exception>
#include "SimServices.h"
#include "ConsoleManager.h"
#include "HardwareElementBase.h"


class Encoder : public HardwareElementBase
{
private:

public:
	Encoder(HardwareElementBase& base)
		: HardwareElementBase(base)
	{}
};
