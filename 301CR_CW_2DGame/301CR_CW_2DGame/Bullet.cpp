#include "Bullet.h"
#include "Data_Sub.h"

typedef luabridge::LuaRef lua_r;

Bullet::Bullet(float pos_x, float pos_y, lua_State* lua_file)
{
	InitBulletTexture(lua_file);

	// Initalize Bullet's posion( Bullet need to appear in fornt of Player),
	// Direction
	// and Speed
	Bullet_Shape.setPosition(pos_x, pos_y);

	lua_r b = luabridge::getGlobal(lua_file, "bullet");

	lua_r Dir_x = b["Dir_x"];
	lua_r Dir_y = b["Dir_y"];
	lua_r b_speed = b["Bulletspeed"];

	Bullet_Dir.x = Dir_x.cast<float>();
	Bullet_Dir.y = Dir_y.cast<float>();
	Bullet_speed = b_speed.cast<float>();

	//std::cout << "Bullet shooting" << std::endl;
}

Bullet::~Bullet()
{
}

const sf::Vector2f Bullet::getPos() const
{
	return Bullet_Shape.getPosition();
}

void Bullet::Update()
{
	Bullet_Shape.move(Bullet_Dir.x * Bullet_speed , Bullet_Dir.y * Bullet_speed);
}

void Bullet::Render(sf::RenderWindow* mp_window)
{
	mp_window->draw(this->Bullet_Shape);

}



void Bullet::InitBulletTexture(lua_State* lua_file)
{
	// Initialize Bullet size, texture
	lua_r t = luabridge::getGlobal(lua_file, "bullet");
	std::string Bullet_textureTemp = t["texture"].cast<std::string>();

	lua_r size = t["size"];
	this->Bullet_Shape.setSize(sf::Vector2f(size["width"].cast<float>(), size["height"].cast<float>()));

	if (!Bullet_texture.loadFromFile(Bullet_textureTemp))
	{
		std::cout << "Bullet Texture did not load!" << "\n";
	}
	Bullet_Shape.setTexture(&Bullet_texture);


}

const sf::FloatRect Bullet::getBounds() const
{
	return Bullet_Shape.getGlobalBounds();
}