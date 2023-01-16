#pragma once
#include <algorithm>
#include "SubSystem_Manager.h"

extern "C" {
#include <include/lua.h>
#include <include/lauxlib.h>
#include <include/lualib.h>
}
#include <LuaBridge\LuaBridge.h>
#include <fstream>

typedef luabridge::LuaRef lua_r;

// This is the Data subsystem. 
// This system can allow to read LUA file from the data folder.
// Need to pass the file path and the GetLuaFile can read the file.
class Data_Sub :
    public SubSystem_Manager
{
public:
    static lua_State* GetLuaFile(const char* file_path);
};

