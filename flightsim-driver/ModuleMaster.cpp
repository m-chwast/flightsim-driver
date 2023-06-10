#include "ModuleMaster.h"

void ModuleMaster::Initialize()
{
    for (ModuleBase& m : _modules)
    {
        m.Initialize();
    }
}

void ModuleMaster::Manage()
{
    for (ModuleBase& m : _modules)
    {
        m.Manage();
    }
}
