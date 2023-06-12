#include "FlightControlUnit.h"

typedef enum
{
	EVENT_AUTO_THROTTLE_ARM_TOGGLE,
} EventType;

FlightControlUnit::FlightControlUnit(const SimServices& simServices)
	: ModuleHardware(simServices)
{
	_name = "FCU";
}

void FlightControlUnit::Initialize()
{
	PrintInitMessage();


}

void FlightControlUnit::Manage()
{

}
