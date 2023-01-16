#pragma once
#include "SubSystem_Manager.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

// This is the UI Subsystem.
// Used imgui and imgui-sfml.
// The UI subsystem has its own window.

// Tried to put the UI screen in same window, but have a problem.
// The problem was that make connection  graphic's pollevent and sf::RenderWindow with UI_Subsystem.
// Because imgui-sfml need same process like sfml graphics so it needs pollevent and sf::RenderWindow.
// Could not find other way to make them in same window because do not have enough time to do.
// Next time, I will try to connect with them.
class UI_Sub : SubSystem_Manager
{
public:
	UI_Sub() {};
	~ UI_Sub();

	sf::RenderWindow* mp_imguiWindow;
	sf::Event event{};
	// For updating UI
	sf::Clock deltaTime;
	sf::VideoMode UI_Info{};

	void InitUI(lua_State* lua_file);
	void UpdateSubsystem();
private:
	void HandleEvent();


};

