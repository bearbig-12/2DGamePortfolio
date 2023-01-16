#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Event.h"
#include "EventHandler.h"

extern "C" {
#include <include/lua.h>
#include <include/lauxlib.h>
#include <include/lualib.h>
}

class Player
{
public:
	Player(lua_State* lua_file);
	~Player();

public:
	void InitPlayerTexture(lua_State* lua_file);

	void Render(sf::RenderWindow* mp_window);
	const sf::Vector2f getPlayerPos() const;
	const sf::FloatRect getBounds() const;

	sf::RectangleShape Player_Shape;

	static int Player_Hp;


private:
	sf::Texture Player_texture;
	int Player_HP_Max;


};