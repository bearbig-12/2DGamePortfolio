#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Event.h"
#include "EventHandler.h"
#include "RectCollider.h"
#include <string>

extern "C" {
#include <include/lua.h>
#include <include/lauxlib.h>
#include <include/lualib.h>
}
class Wall
{
public:
	Wall() {};
	Wall(lua_State* lua_file, std::string type);
	~Wall() {};

	void Render(sf::RenderWindow* mp_window);

public:
	sf::RectangleShape Wall_Shape;

private:
	void InitGround(lua_State* lua_file);
private:
	sf::Texture Wall_Texture;

};

