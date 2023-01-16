#pragma once

extern "C" {
#include <include/lua.h>
#include <include/lauxlib.h>
#include <include/lualib.h>
}

#include <LuaBridge\LuaBridge.h>

class SubSystem_Manager
{
	// Need to ask why
	virtual void UpdateSubsystem() = 0;
};

