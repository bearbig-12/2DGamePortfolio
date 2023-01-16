#include "Sound_Sub.h"
#include "Data_Sub.h"
typedef luabridge::LuaRef lua_r;


Sound_Sub::Sound_Sub()
{
}
// Initialize two kinds of gun sound and Hurt sound
void Sound_Sub::InitSound(lua_State* lua_file)
{
	lua_r s = luabridge::getGlobal(lua_file, "Sound");
	std::string Gun_SoundEff = s["gun"].cast<std::string>();
	std::string Gun_SoundEff2 = s["gun2"].cast<std::string>();
	std::string Hurt_SoundEff = s["damage"].cast<std::string>();


	if (!Sound_Buffer_Gun.loadFromFile(Gun_SoundEff))
	{
		std::cout << "Gun Sound Not loaded!" << std::endl;
	}
	if (!Sound_Buffer_Gun2.loadFromFile(Gun_SoundEff2))
	{
		std::cout << "Gun2 Sound Not loaded!" << std::endl;
	}
	if (!Hurt_Buffer.loadFromFile(Hurt_SoundEff))
	{
		std::cout << "Gun2 Sound Not loaded!" << std::endl;
	}

}

void Sound_Sub::PlayShootingSound()
{
	// Using rand(), can play random gun sound.
	int i = rand() % 2;
	if (i == 0)
	{
		mSound.setBuffer(Sound_Buffer_Gun);
		mSound.setVolume(5.0f);
		mSound.play();
	}
	if (i == 1)
	{
		mSound.setBuffer(Sound_Buffer_Gun2);
		mSound.setVolume(10.0f);
		mSound.play();
	}

}

void Sound_Sub::PlayDamageSound()
{
	mSound2.setBuffer(Hurt_Buffer);
	mSound2.setVolume(5.0f);
	mSound2.play();
}



void Sound_Sub::UpdateSubsystem()
{
	HandleEvent();
}

void Sound_Sub::HandleEvent()
{
	for (Event* event : EventHandler::GetEvents()) {
		switch (event->GetEventType())
		{
		case EventType::PlayGunSound:
			PlayShootingSound();
			break;
		case EventType::getDamage:
			PlayDamageSound();
			break;
		}


	}
}


