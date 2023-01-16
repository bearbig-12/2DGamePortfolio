#pragma once
#include "SFML/Audio.hpp"
#include "Data_Sub.h"
#include "Event.h"
#include "EventHandler.h"
#include <string>
#include <iostream>
#include <vector>
// This is the sounds Subsystem.
// When player get damaged (collision check with enemy) and Shooting bullet,
// new sounds event come into this subsystem and play the sounds.
class Sound_Sub : SubSystem_Manager
{
public:
    Sound_Sub();
    ~Sound_Sub() {};
    void InitSound(lua_State* lua_file);
    void PlayShootingSound();
    void PlayDamageSound();

    void HandleEvent();
    void UpdateSubsystem();



    sf::SoundBuffer Hurt_Buffer;
    sf::SoundBuffer Sound_Buffer_Gun;
    sf::SoundBuffer Sound_Buffer_Gun2;
    sf::SoundBuffer Sound_Buffer2;

   sf::Sound mSound;
   sf::Sound mSound2;

};

