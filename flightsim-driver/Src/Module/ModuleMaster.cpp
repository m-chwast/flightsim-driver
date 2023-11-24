#include "ModuleMaster.h"
#include "FlightControlUnit.h"


ModuleMaster::ModuleMaster(const ModuleUtils& utils)
    : ModuleBase(utils)
{
    _name = "Master";

    FlightControlUnit* flightControlUnit = new FlightControlUnit(utils, 1);
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
