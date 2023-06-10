#pragma once

class ModuleBase
{
public:
	
	virtual bool Initialize() = 0;
	virtual bool Manage() = 0;
};
