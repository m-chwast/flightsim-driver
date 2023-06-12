#include "ModuleMaster.h"
#include "FlightControlUnit.h"

ModuleMaster::ModuleMaster()
{
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
    for (ModuleBase* m : _modules)
    {
        m->Manage();
    }
}
