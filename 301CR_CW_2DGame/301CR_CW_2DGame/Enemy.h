#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Event.h"
#include "EventHandler.h"
#include "RectCollider.h"

extern "C" {
#include <include/lua.h>
#include <include/lauxlib.h>
#include <include/lualib.h>
}


class Enemy
{
public:
	// The Enemy respawn random position 
	Enemy(float pos_x, float pos_y, lua_State* lua_file);
	~Enemy();


	void Update();
	void Render(sf::RenderWindow* mp_window);

	// To get Enemy's sprite postion
	const sf::Vector2f getPos() const;
	// To get GlobalBounds for Collision checking
	const sf::FloatRect getBounds() const;

	sf::RectangleShape Enemy_Shape;

private:
	sf::Texture Enemy_Texture;
	float Enemy_dir;
	void InitEnemy(lua_State* lua_file);



};

