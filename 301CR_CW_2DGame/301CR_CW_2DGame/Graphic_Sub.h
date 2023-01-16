#pragma once


#include "SFML/Graphics.hpp"
#include <SFML/System/Clock.hpp>

#include "Event.h"
#include "EventHandler.h"
#include "SubSystem_Manager.h"
#include "GameEngine.h"
#include "Physics_Sub.h"
#include "RectCollider.h"
#include "Sound_Sub.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <string>
#include <sstream>


//Game Objects
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Wall.h"

class Graphic_Sub :
    public SubSystem_Manager
{

public:
    //Cons & Destructor
    Graphic_Sub() {};
    virtual ~Graphic_Sub();

    void UpdateSubsystem();

public:
    // Initialize graphics. The graphic information comes from Lua File.
    int InitGraphicsLua(lua_State* lua_file);
    // Initalize models which use in game (ex Player, Wall)
    void InitModels(lua_State* lua_level_file);
    // Initalize Enemy objects.
    void InitEnemy(lua_State* lua_file);
    void InitText(lua_State* lua_file);
    void PollEvent();
    // When player want to change the level, 
    // need to clear the objects which exist in current scene.
    void UnloadLevel();

    //void UpdateMousePos();

   
    void UpdateBullets();


    // This is the Collision check function
    // This function check bullet and Enemy Collision detection, and
    // also check between player and Enemy
    void BulletEnemyCheck();

private:
    void HandleEvent();

    sf::RenderWindow* mp_window{};
    sf::VideoMode VideoInfo{};
    sf::Event ev{};

    sf::Vector2i mousePos;
    sf::Vector2f mousePos_View;

    lua_State* level_file;

private:
    //Player
    Player* Main_Player;

    //Enemy
    //sf::RectangleShape Enemy;
    //sf::Texture Enemy_Texture;
    //std::vector<sf::RectangleShape> Enemies;

    // Enemy
    Enemy* enemy;
    std::vector<Enemy*> Enemies_container;
    float Spawn_Timer;
    float MaxSpawn_Timer;
    unsigned int Max_Enemy;
   
    void UpdateEnemies();

    //Bullet
    Bullet* bullet;
    std::vector<Bullet*> Bullets_container;

    // Ground & Wall
    Wall* Ground;
    Wall* LeftWall;
    Wall* RightWall;
    Wall* TopWall;


    //Collider
    // Player
    RectCollider* Player_Collider;

    //Bullet Collider
    RectCollider* Bullet_Collider;
    std::vector<RectCollider*> Bullets_Coll_Container;

    //Enemy Collider
    RectCollider* Enemy_Collider;
    std::vector<RectCollider*> Enemy_Coll_Container;

    RectCollider* Ground_Collider;
    std::vector<RectCollider*> Ground_Coll_Container;


    // Text
    sf::Text Text;
    sf::Text GameOverText;
    sf::Font Font;
};

