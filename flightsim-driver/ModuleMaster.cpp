#include "ModuleMaster.h"
#include "FlightControlUnit.h"

ModuleMaster::ModuleMaster()
{
    _name = "Master";

    FlightControlUnit* flightControlUnit = new FlightControlUnit();
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
