#include "ModuleMaster.h"
#include "FlightControlUnit.h"

ModuleMaster::ModuleMaster(const SimServices& simServices, ConsoleManager& console)
    : ModuleBase(simServices, console)
{
    _name = "Master";

    FlightControlUnit* flightControlUnit = new FlightControlUnit(simServices, _console, 0);
    _modules.push_back(flightControlUnit);
}

void ModuleMaster::Initialize()
{
    PrintInitMessage();
    for (ModuleHardware* m : _modules)
    {
        m->Initialize();
    }
}

void ModuleMaster::Manage()
{
    if (_initialized != true)
    {
        Initialize();
        _initialized = true;
    }

    for (ModuleHardware* m : _modules)
    {
        m->Manage();
    }
}

ModuleHardware* ModuleMaster::GetModule(unsigned long moduleID) const
{
    for (ModuleHardware* m : _modules)
    {
        if (m->GetID() == moduleID)
            return m;
    }
    return nullptr;
}
