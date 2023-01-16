#include "Player.h"
#include "Data_Sub.h"
typedef luabridge::LuaRef lua_r;

int Player::Player_Hp;

Player::Player(lua_State* lua_file)
{
	InitPlayerTexture(lua_file);

	//std::cout << Player_Shape.getSize().x << " : " << Player_Shape.getSize().y << std::endl;

}

Player::~Player()
{
}



void Player::InitPlayerTexture(lua_State* lua_file)
{
	lua_r t = luabridge::getGlobal(lua_file, "player");

	lua_r size = t["size"];
	lua_r pos = t["position"];
	lua_r HP = t["HpMax"];

	Player_Shape.setPosition(sf::Vector2f(pos["X"].cast<float>(), pos["Y"].cast<float>()));
	Player_Shape.setSize(sf::Vector2f(size["x"].cast<float>(), size["y"].cast<float>()));
	
	Player_HP_Max = HP.cast<int>();
	Player_Hp = Player_HP_Max;

	std::string Player_textureTemp = t["texture"].cast<std::string>();
	if (!Player_texture.loadFromFile(Player_textureTemp))
	{
		std::cout << "Player Texture did not load!" << "\n";
	}

	Player_Shape.setTexture(&Player_texture);


}
void Player::Render(sf::RenderWindow* mp_window)
{
	mp_window->draw(this->Player_Shape);
}



const sf::Vector2f Player::getPlayerPos() const
{
	return Player_Shape.getPosition();
}
const sf::FloatRect Player::getBounds() const
{
	return Player_Shape.getGlobalBounds();
}




