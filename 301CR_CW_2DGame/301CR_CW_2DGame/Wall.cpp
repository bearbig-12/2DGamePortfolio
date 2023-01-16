#include "Wall.h"
#include "Data_Sub.h"
typedef luabridge::LuaRef lua_r;

// The Wall Object has 4 types.
// Because of the Wall object, player cannot run over the screen.
Wall::Wall(lua_State* lua_file, std::string type)
{
	if (type == "ground")
	{
		lua_r w = luabridge::getGlobal(lua_file, "Ground");

		lua_r size = w["size"];
		lua_r pos = w["position"];



		Wall_Shape.setPosition(sf::Vector2f(pos["X"].cast<float>(), pos["Y"].cast<float>()));
		Wall_Shape.setSize(sf::Vector2f(size["x"].cast<float>(), size["y"].cast<float>()));

		std::string wall_textureTemp = w["texture"].cast<std::string>();
		//std::cout << wall_textureTemp << std::endl;
		if (!Wall_Texture.loadFromFile(wall_textureTemp))
		{
			std::cout << "Wall Texture did not load!" << "\n";
		}

		Wall_Shape.setTexture(&Wall_Texture);

	}
	else if (type == "LeftWall")
	{
		lua_r w = luabridge::getGlobal(lua_file, "WallLeft");

		lua_r size = w["size"];
		lua_r pos = w["position"];



		Wall_Shape.setPosition(sf::Vector2f(pos["X"].cast<float>(), pos["Y"].cast<float>()));
		Wall_Shape.setSize(sf::Vector2f(size["x"].cast<float>(), size["y"].cast<float>()));

		std::string wall_textureTemp = w["texture"].cast<std::string>();
		//std::cout << wall_textureTemp << std::endl;
		if (!Wall_Texture.loadFromFile(wall_textureTemp))
		{
			std::cout << "Wall Texture did not load!" << "\n";
		}

		Wall_Shape.setTexture(&Wall_Texture);
	}
	else if (type == "RightWall")
	{
		lua_r w = luabridge::getGlobal(lua_file, "WallRight");

		lua_r size = w["size"];
		lua_r pos = w["position"];



		Wall_Shape.setPosition(sf::Vector2f(pos["X"].cast<float>(), pos["Y"].cast<float>()));
		Wall_Shape.setSize(sf::Vector2f(size["x"].cast<float>(), size["y"].cast<float>()));

		std::string wall_textureTemp = w["texture"].cast<std::string>();
		//std::cout << wall_textureTemp << std::endl;
		if (!Wall_Texture.loadFromFile(wall_textureTemp))
		{
			std::cout << "Wall Texture did not load!" << "\n";
		}

		Wall_Shape.setTexture(&Wall_Texture);
	}
	else if (type == "TopWall")
	{
		lua_r w = luabridge::getGlobal(lua_file, "WallTop");

		lua_r size = w["size"];
		lua_r pos = w["position"];



		Wall_Shape.setPosition(sf::Vector2f(pos["X"].cast<float>(), pos["Y"].cast<float>()));
		Wall_Shape.setSize(sf::Vector2f(size["x"].cast<float>(), size["y"].cast<float>()));

		std::string wall_textureTemp = w["texture"].cast<std::string>();
		//std::cout << wall_textureTemp << std::endl;
		if (!Wall_Texture.loadFromFile(wall_textureTemp))
		{
			std::cout << "Wall Texture did not load!" << "\n";
		}

		Wall_Shape.setTexture(&Wall_Texture);
	}
	else
	{
		std::cout << "Wrong Type" << std::endl;
	}

}

void Wall::Render(sf::RenderWindow* mp_window)
{
	mp_window->draw(Wall_Shape);
}

void Wall::InitGround(lua_State* lua_file)
{


	//Wall_Shape.setFillColor(sf::Color::Green);

	//std::string wall_textureTemp = w["texture"].cast<std::string>();
	//if (!Wall_Texture.loadFromFile(wall_textureTemp))
	//{
	//	std::cout << "Wall Texture did not load!" << "\n";
	//}

	//Wall_Shape.setTexture(&Wall_Texture);
	
}
