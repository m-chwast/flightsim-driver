#include "ModuleMaster.h"

bool ModuleMaster::Initialize()
{
    for (ModuleBase& m : _modules)
    {
        m.Initialize();
    }
    return true;
}

bool ModuleMaster::Manage()
{
    for (ModuleBase& m : _modules)
    {
        m.Manage();
    }
    return true;
}
