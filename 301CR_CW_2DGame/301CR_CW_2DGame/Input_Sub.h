#pragma once
#include "SubSystem_Manager.h"
#include "Event.h";
#include "EventHandler.h";
#include <chrono>
#include <SFML/Window/Keyboard.hpp>

class Input_Sub :
    public SubSystem_Manager
{
public:
	Input_Sub() {};
	~Input_Sub() {};

	// initialise input key binds. 
	void InitInput(lua_State* lua_file);
	// Update the input subsystem
	virtual void UpdateSubsystem();

	// Time varaibles for Shooting Cooldown
	static float CoolDownShooting;
	static float CoolDownShootingMax;

	static bool CoolDown();
	static void CoolDownUpdate();
protected:
	
	// Lua file used to initialise for keyboard subsystem
	lua_State* lua_control_file{}; 

	// Input Variables
	// Check key is Pressed
	std::map<int, bool> Keys; 
	// For SFML keys
	static std::vector<sf::Keyboard::Key> Sfml_keys; 
	int m_key{}; // Stores a pressed button.



};

