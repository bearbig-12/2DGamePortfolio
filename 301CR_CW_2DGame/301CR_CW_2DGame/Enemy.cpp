#include "Enemy.h"
#include "Data_Sub.h"

#include "RectCollider.h"

typedef luabridge::LuaRef lua_r;

Enemy::Enemy(float pos_x, float pos_y, lua_State* lua_file)
{
	
	InitEnemy(lua_file);
	Enemy_Shape.setPosition(pos_x, pos_y);
	

}

Enemy::~Enemy()
{
}

void Enemy::InitEnemy(lua_State* lua_file)
{
	lua_r t = luabridge::getGlobal(lua_file, "enemy");

	lua_r size = t["size"];
	lua_r dir = t["EnemyDir"];
	Enemy_Shape.setSize(sf::Vector2f(size["width"].cast<float>(), size["height"].cast<float>()));
	Enemy_dir = dir.cast<float>();
	std::string Enemy_textureTemp = t["texture"].cast<std::string>();
	if (!Enemy_Texture.loadFromFile(Enemy_textureTemp))
	{
		std::cout << "Enemy Texture did not load!" << "\n";
	}
	Enemy_Shape.setTexture(&Enemy_Texture);
}



void Enemy::Update()
{
	// This function allow to move bullet shape.
	// However, When the shape's position is changed, also need to change the Collider Position.
	Enemy_Shape.move(Enemy_dir, 0.0f);
}



void Enemy::Render(sf::RenderWindow* mp_window)
{
	mp_window->draw(this->Enemy_Shape);

}

const sf::Vector2f Enemy::getPos() const
{
	return Enemy_Shape.getPosition();
}

const sf::FloatRect Enemy::getBounds() const
{
	return Enemy_Shape.getGlobalBounds();
}

