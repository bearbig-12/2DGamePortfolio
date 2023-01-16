#include "KeyBoard.h"

//float Input_Sub::CoolDownShooting;
//float Input_Sub::CoolDownShootingMax;

KeyBoard::KeyBoard()
{
}
// If the players press the key, The function makes event and give it to other subsystems
void KeyBoard::GetInput()
{
    if (CoolDownShooting >= CoolDownShootingMax)
    {
        CoolDownShooting = 0.0f;
        keypressed = true;
    }
    else
    {
        keypressed = false;

    }
    // W A S D space input keys
    if (sf::Keyboard::isKeyPressed(Input_Sub::Sfml_keys[0]))
        HandleButton(Input_Sub::Sfml_keys[0]);

    if (sf::Keyboard::isKeyPressed(Input_Sub::Sfml_keys[1]))
        HandleButton(Input_Sub::Sfml_keys[1]);

    if (sf::Keyboard::isKeyPressed(Input_Sub::Sfml_keys[2]))
        HandleButton(Input_Sub::Sfml_keys[2]);

    if (sf::Keyboard::isKeyPressed(Input_Sub::Sfml_keys[3]))
        HandleButton(Input_Sub::Sfml_keys[3]);

    if (sf::Keyboard::isKeyPressed(Input_Sub::Sfml_keys[4]))
    {
        HandleButton(Input_Sub::Sfml_keys[4]);

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        Event* Quit_Game = new Event(EventType::Quit);
        EventHandler::AddEvent(Quit_Game);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
    {
        Event* nextlevel = new Event(EventType::LoadLevel);
        EventHandler::AddEvent(nextlevel);
    }

}

void KeyBoard::HandleButton(int key)
{
    m_key = key;
    Keys[m_key] = true;
    //std::cout << "Key pressed: " << m_key << " : " << Keys[m_key] << std::endl;

    // W[22], S[18], A[0], D[3], space[57]

    if (m_key == 22)
    {
        Event* MoveUp = new Event(EventType::W);
        EventHandler::AddEvent(MoveUp);
    }
    if (m_key == 18)
    {
        Event* MoveDown = new Event(EventType::S);
        EventHandler::AddEvent(MoveDown);
    }
    if (m_key == 0)
    {
        Event* MoveLeft = new Event(EventType::A);
        EventHandler::AddEvent(MoveLeft);
    }
    if (m_key == 3)
    {
       Event* MoveRight = new Event(EventType::D);
       EventHandler::AddEvent(MoveRight);
    }
    if (m_key == 57 && keypressed)
    {
        Event* Shot = new Event(EventType::Shooting);
        EventHandler::AddEvent(Shot);

        
           
    }
   
}

