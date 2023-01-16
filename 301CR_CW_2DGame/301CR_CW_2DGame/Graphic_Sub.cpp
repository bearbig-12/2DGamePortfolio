#include "Graphic_Sub.h"
#include "Data_Sub.h"
typedef luabridge::LuaRef lua_r;
#include "Score_Sub.h"
Graphic_Sub::~Graphic_Sub()
{
	delete mp_window;

	delete Main_Player;


	//for (auto& e : Bullets_container)
	//{
	//	delete e;
	//}
	//for (auto& e : Enemies_container)
	//{
	//	delete e;
	//}
	delete Ground;
	delete LeftWall;
	delete RightWall;
	delete TopWall;


}



int Graphic_Sub::InitGraphicsLua(lua_State* lua_file)
{
	lua_r graphic = luabridge::getGlobal(lua_file, "Graphics");
	lua_r title = graphic["title"];
	lua_r width = graphic["width"];
	lua_r height = graphic["height"];

	std::string titleString = title.cast<std::string>();
	VideoInfo.height = height.cast<int>();
	VideoInfo.width = width.cast<int>();

	mp_window = new sf::RenderWindow(VideoInfo, titleString);

	InitText(lua_file);


	mp_window->setFramerateLimit(60);  //Frame Limit
	return 0;
}

// Initialize the models based on Lua_level_file.
// Each level has different object's size, texture and so on.
// Based on the level file, initialize objects
void Graphic_Sub::InitModels(lua_State* lua_level_file)
{
	level_file = lua_level_file;
	InitEnemy(level_file);
	Main_Player = new Player(level_file);
	Player_Collider = new RectCollider(Main_Player->Player_Shape, 0);
	
	
	LeftWall = new Wall(Data_Sub::GetLuaFile("Data/geometry.lua"), "LeftWall");
	Ground_Collider = new RectCollider(LeftWall->Wall_Shape, 3);
	Ground_Coll_Container.push_back(Ground_Collider);

	TopWall = new Wall(Data_Sub::GetLuaFile("Data/geometry.lua"), "TopWall");
	Ground_Collider = new RectCollider(TopWall->Wall_Shape, 3);
	Ground_Coll_Container.push_back(Ground_Collider);


	RightWall = new Wall(Data_Sub::GetLuaFile("Data/geometry.lua"), "RightWall");
	Ground_Collider = new RectCollider(RightWall->Wall_Shape, 3);
	Ground_Coll_Container.push_back(Ground_Collider);

	Ground = new Wall(Data_Sub::GetLuaFile("Data/geometry.lua"), "ground");
	Ground_Collider = new RectCollider(Ground->Wall_Shape, 3);
	Ground_Coll_Container.push_back(Ground_Collider);

}

// Initilize Enemy's variables.
// Max Enemy, Spawn time
void Graphic_Sub::InitEnemy(lua_State* lua_file)
{
	lua_r e = luabridge::getGlobal(lua_file, "enemy");
	lua_r Max_Enemis = e["MaxE"];
	lua_r SpawnTime = e["SpawnT"];
	lua_r MaxSpawnTime = e["MaxSpawnT"];

	MaxSpawn_Timer = MaxSpawnTime.cast<float>();
	Spawn_Timer = MaxSpawn_Timer;
	Max_Enemy = Max_Enemis.cast<unsigned int>();
	//Max_Enemy = 1;

}

void Graphic_Sub::InitText(lua_State* lua_file)
{
	lua_r font = luabridge::getGlobal(lua_file, "Graphics");

	std::string fonttmep = font["font"].cast<std::string>();
	int size = font["fontsize"].cast<int>();

	if (!Font.loadFromFile(fonttmep))
	{
		std::cout << "Font not loaded" << std::endl;
	}

	Text.setFont(Font);
	std::stringstream temp;
	temp << "Highest Score : " << Score_Sub::GetHighestScore();
	Text.setString(temp.str());
	Text.setCharacterSize(size);
	Text.setFillColor(sf::Color::Red);


	int overfont = font["Overfontsize"].cast<int>();

	GameOverText.setFont(Font);
	GameOverText.setString("Game Over!!!");
	GameOverText.setCharacterSize(overfont);
	GameOverText.setFillColor(sf::Color::Red);
}




void Graphic_Sub::PollEvent()
{
	if (this->mp_window->isOpen())
	{
		if (mp_window->pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
			{
				Event* Quit_Game = new Event(EventType::Quit);
				EventHandler::AddEvent(Quit_Game);

			}
			break;

			default:
				break;
			}
		}
	}
}



void Graphic_Sub::UpdateSubsystem()
{
	// if the player hp is bigger than 0, the user can play the game.
	// Hoever the hp is <= 0, will show the game over screen
	if (Player::Player_Hp > 0)
	{


		PollEvent();
		// Set up for Collider objects
		Physics_Sub::world.Step(1.0f / 60.0f, 8, 3);


		//render
		mp_window->clear(sf::Color::Black);




		//Draw Game obj
		Main_Player->Render(mp_window);

		//Bullets
		// Rendering  Bullets and Update
		for (auto& b : Bullets_container)
		{
			b->Render(mp_window);
		}
		UpdateBullets();


		// Wall Objects
		// Rendering Wall's
		Ground->Render(mp_window);
		LeftWall->Render(mp_window);
		RightWall->Render(mp_window);
		TopWall->Render(mp_window);

		//Enemies
		UpdateEnemies();
		for (auto& e : Enemies_container)
		{
			// Rendering Enemies
			e->Render(mp_window);
		}

		//Mouse pos
		//UpdateMousePos();

		BulletEnemyCheck();

		HandleEvent();

		// Attached the collider to Object shape.
		// For this, change the Physics postion to Graphics postion.
		// When player collider's velocity is changed it means collider's position is also changed.
		// Because of that, need to change the  Player_shape's postion.
		// Based on that, the collider is attached to Player_shape(graphics)
		Player_Collider->PhysicsToGraphicsPos(Main_Player->Player_Shape);

		mp_window->draw(Text);

		//render
		mp_window->display();
	}
	if (Player::Player_Hp <= 0)
	{
		mp_window->clear(sf::Color::Black);
		mp_window->draw(GameOverText);
		mp_window->display();
	
	}
}


//void Graphic_Sub::UpdateMousePos()
//{
//	mousePos = sf::Mouse::getPosition(*mp_window);
//	mousePos_View = mp_window->mapPixelToCoords(mousePos);
//}


// Spwaning Enemey by time and number of enemies
// if currnet ememies which is on screen is more that Max enemy,
// it does not spwan more enemies;
void Graphic_Sub::UpdateEnemies()
{

	
	if (Enemies_container.size() < Max_Enemy)
	{
		if (Spawn_Timer >= MaxSpawn_Timer)
		{
			enemy = new Enemy(
				static_cast<float>(mp_window->getSize().x - 10.0f),
				static_cast<float>(rand() % static_cast<int>(mp_window->getSize().y)) - 150.0f,
				level_file);
			Enemies_container.push_back(enemy);


			Enemy_Collider = new RectCollider(enemy->Enemy_Shape, 2);
			Enemy_Coll_Container.push_back(Enemy_Collider);



			Spawn_Timer = 0.f;
		}
		else
		{
			Spawn_Timer += 1.0f;
		}
	}

	
}


void Graphic_Sub::UpdateBullets()
{
	for (int i = 0; i < Bullets_container.size(); i++)
	{

		Bullets_container[i]->Update();
		// When bullet's poisition is changed, need to update the bullet collider's position.
		// For that, need to use GraphicsToPhysicsPos function.
		// This is not good becuase the physics function is updating in graphics.
		// But, I do not have time to make it, and, at that point, I could not find other way.
		// If I have next chance to make, I will make it seperately. Both susbsytem get Envent, and
		// Graphics and Physics update in their own update function.
		Bullets_Coll_Container[i]->GraphicsToPhysicsPos(Bullets_container[i]->Bullet_Shape);

		sf::Vector2f Bullet_pos = Bullets_container[i]->getPos();
		// If bullet go outside of the screen, delete it.
		if (Bullet_pos.x > 1600)
		{
			delete Bullets_container[i];
			Bullets_container.erase(Bullets_container.begin() + i);
			delete Bullets_Coll_Container[i];
			Bullets_Coll_Container.erase(Bullets_Coll_Container.begin() + i);
		}

	}
}

void Graphic_Sub::BulletEnemyCheck()
{
	// This is the collision check function. Tried to do box2d's contact listender for the
	// Collision check but it was not clear to use my game, also I did not understand it..
	// The hardest point was get fixture's information.
	// Added userdata to fixture but cannot get the data when the collision check happened.
	// Next time, if I have more time, I will try to use box2d's collision check function.
	for (int i = 0; i < Enemies_container.size(); i++)
	{
		// we have two delete function in this for loop.
		// It can cause a problem because it can delete in same time (twice)
		// So I add a bool to check
		bool enemyRemoved = false;
		Enemies_container[i]->Update();
		Enemy_Coll_Container[i]->GraphicsToPhysicsPos(Enemies_container[i]->Enemy_Shape);

		sf::Vector2f Enemy_pos = Enemies_container[i]->getPos();
		b2Vec2 Enemy_pos2 = Enemy_Coll_Container[i]->Object->GetPosition();
		

		for (int k = 0; k < Bullets_container.size() && !enemyRemoved; k++)
		{
			// Bullet & Eenemy
			if (Bullets_container[k]->getBounds().intersects(Enemies_container[i]->getBounds()))
			{
				delete Enemies_container[i];
				Enemies_container.erase(Enemies_container.begin() + i);
				delete Enemy_Coll_Container[i];
				Enemy_Coll_Container.erase(Enemy_Coll_Container.begin() + i);


				delete Bullets_container[k];
				Bullets_container.erase(Bullets_container.begin() + k);
				delete Bullets_Coll_Container[k];
				Bullets_Coll_Container.erase(Bullets_Coll_Container.begin() + k);

				Event* AddPoint = new Event(EventType::EnemyDestoryed);
				EventHandler::AddEvent(AddPoint);

				enemyRemoved = true;
			}
		}
		
		if (!enemyRemoved)
		{
			
			if (Enemy_pos.x < 0)
			{
				delete Enemies_container[i];
				Enemies_container.erase(Enemies_container.begin() + i);
				delete Enemy_Coll_Container[i];
				Enemy_Coll_Container.erase(Enemy_Coll_Container.begin() + i);

				enemyRemoved = true;
			}
			// Player & Eenemy
			else if (Enemies_container[i]->getBounds().intersects(Main_Player->getBounds()))
			{
				delete Enemies_container[i];
				Enemies_container.erase(Enemies_container.begin() + i);
				delete Enemy_Coll_Container[i];
				Enemy_Coll_Container.erase(Enemy_Coll_Container.begin() + i);

				Event* Hurt = new Event(EventType::getDamage);
				EventHandler::AddEvent(Hurt);

				enemyRemoved = true;
			}
		}


	}
}


void Graphic_Sub::UnloadLevel()
{
	delete mp_window;
	delete Main_Player;
	delete Player_Collider;

	

	for (auto& e : Bullets_container)
	{
		delete e;
	}
	for (auto& e : Enemies_container)
	{
		delete e;
	}
	for (auto& e : Bullets_Coll_Container)
	{
		delete e;
	}
	for (auto& e : Enemy_Coll_Container)
	{
		delete e;
	}
	delete Ground;
	delete LeftWall;
	delete RightWall;
	delete TopWall;

	for (auto& e : Ground_Coll_Container)
	{
		delete e;
	}
	
	Bullets_Coll_Container.clear();
	Enemy_Coll_Container.clear();
	Ground_Coll_Container.clear();
	Bullets_container.clear();
	Enemies_container.clear();

}


void Graphic_Sub::HandleEvent()
{
	// When the event handler get w,a,s,d and space event,
	// set the player collider's velocity, so the player collider is moveing.	
	for (Event* event : EventHandler::GetEvents())
	{
		switch (event->GetEventType())
		{
		case EventType::A:
			Player_Collider->Object->SetLinearVelocity(b2Vec2(-5.0f, 0.0f));
			break;
		case EventType::D:
			Player_Collider->Object->SetLinearVelocity(b2Vec2(5.0f, 0.0f));
			break;
		case EventType::W:
			Player_Collider->Object->SetLinearVelocity(b2Vec2(0.0f, 5.0f));

			break;
		case EventType::S:
			Player_Collider->Object->SetLinearVelocity(b2Vec2(0.0f, -5.0f));
			break;
		case EventType::Shooting:
		{
			bullet = new Bullet(
				Main_Player->getPlayerPos().x + 200.0f,
				Main_Player->getPlayerPos().y + 25.0f,
				level_file);
			this->Bullets_container.push_back(bullet);
			Bullet_Collider = new RectCollider(bullet->Bullet_Shape, 1);
			this->Bullets_Coll_Container.push_back(Bullet_Collider);
			Event* GunSound = new Event(EventType::PlayGunSound);
			EventHandler::AddEvent(GunSound);
		}
		
			break;
		default:
			break;
		}

	}

}

