#include "ModuleMaster.h"
#include "FlightControlUnit.h"

ModuleMaster::ModuleMaster(const SimServices& simServices)
    : ModuleBase(simServices)
{
    _name = "Master";

    FlightControlUnit* flightControlUnit = new FlightControlUnit(simServices, 0);
    _modules.push_back(flightControlUnit);
}

void ModuleMaster::Initialize()
{
    PrintInitMessage();
    for (ModuleBase* m : _modules)
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

    for (ModuleBase* m : _modules)
    {
        m->Manage();
    }
}
