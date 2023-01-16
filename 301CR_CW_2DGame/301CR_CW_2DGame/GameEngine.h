#pragma once
#include "Graphic_Sub.h"
#include "Physics_Sub.h"
#include "Input_Sub.h"
#include "Event.h"
#include "Sound_Sub.h"
#include "Score_Sub.h"
#include "UI_Sub.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <Windows.h>

extern "C" {
#include <include/lua.h>
#include <include/lauxlib.h>
#include <include/lualib.h>
}
// This is GameEngine Class
// All Subsystems are initalized when GameEngine Constructor is Called
class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void LoadNextLevel(lua_State* lua_level_file);

public:
	// In the Update Function, Update subsystems.
	void Update();
	void Event_Handler();

	static bool isRunning;
	
};

