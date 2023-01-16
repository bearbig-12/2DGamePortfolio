#include "Data_Sub.h"


lua_State* Data_Sub::GetLuaFile(const char* file_path)
{
	std::fstream check_file;
	check_file.open(file_path);
	if (check_file.fail()) {
		std::cout << "\n[Data error] File (" << file_path << ") not found!\nCheck directory path and typos\n";
	}
	else {
		lua_State* lua_file;
		lua_file = luaL_newstate();
		luaL_dofile(lua_file, file_path); 
		luaL_openlibs(lua_file);
		lua_pcall(lua_file, 0, 0, 0);

		return lua_file;
	}
	check_file.close();
}

// https://www.lua.org/pil/8.4.html
//The pcall function calls its first argument in protected mode, 
//so that it catches any errors while the function is running. 
//If there are no errors, pcall returns true, plus any values returned by the call. Otherwise, it returns false, plus the error message.