#include "Input_Sub.h"
#include "Keyboard.h"
KeyBoard keyboard;
typedef luabridge::LuaRef lua_r;
std::vector<sf::Keyboard::Key> Input_Sub::Sfml_keys;

float Input_Sub::CoolDownShooting;
float Input_Sub::CoolDownShootingMax;

void Input_Sub::InitInput(lua_State* lua_file)
{
    lua_control_file = lua_file;

    // initialize the key binds
    lua_r keyBinds = luabridge::getGlobal(lua_control_file, "keyBinds");
    lua_r k = keyBinds["keyboard"];
    lua_r forward = k["forward"]; // w
    lua_r left = k["left"];       // a
    lua_r backward = k["backward"]; // s
    lua_r right = k["right"];       // d
    lua_r space = k["space"];

    //Init CoolDown
    lua_r CdMax = keyBinds["CoolDownTMax"];
    CoolDownShootingMax = CdMax;

    //std::cout << CoolDownShootingMax << std::endl;

    CoolDownShooting = CoolDownShootingMax;


    if (forward.cast<char>() == 'w')
        Sfml_keys.push_back(sf::Keyboard::Key::W); 
    if (backward.cast<char>() == 's')
        Sfml_keys.push_back(sf::Keyboard::Key::S);
    if (left.cast<char>() == 'a')
        Sfml_keys.push_back(sf::Keyboard::Key::A);
    if (right.cast<char>() == 'd')
        Sfml_keys.push_back(sf::Keyboard::Key::D);
    if (space.cast<char>() == ' ')
        Sfml_keys.push_back(sf::Keyboard::Key::Space);
   
}

void Input_Sub::UpdateSubsystem()
{

    keyboard.GetInput();
    CoolDownUpdate();

}

// Check the Cooldown, Player cannot shoot a bullet after their shot immediately.
bool Input_Sub::CoolDown()
{
    if (CoolDownShooting >= CoolDownShootingMax)
    {
        CoolDownShooting = 0;
        return true;
    }
    return false;

}
void Input_Sub::CoolDownUpdate()
{
    if (CoolDownShooting < CoolDownShootingMax)
    {
        CoolDownShooting += 1.0f;
    }
}