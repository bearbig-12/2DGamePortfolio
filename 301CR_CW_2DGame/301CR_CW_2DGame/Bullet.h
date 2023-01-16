#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

#include "Event.h"
#include "EventHandler.h"

#include <iostream>


extern "C" {
#include <include/lua.h>
#include <include/lauxlib.h>
#include <include/lualib.h>
}

class Bullet
{
public:
	sf::RectangleShape Bullet_Shape;

private:
	sf::Texture Bullet_texture;	
	// Bullet Dir    
	sf::Vector2f Bullet_Dir;
	// Bullet Speed
	float Bullet_speed;


public:
	// Bullet's Texture, position, Direct to move, speed
	Bullet(float pos_x, float pos_y, lua_State* lua_file);
	~Bullet();

	// To get the bullet postion
	const sf::Vector2f getPos() const;

	void Update();
	void Render(sf::RenderWindow* mp_window);
	void InitBulletTexture(lua_State* lua_file);
	// Get Bullet's Bound. It can be used for collision check
	const sf::FloatRect getBounds() const;


};

