#pragma once
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp> 

enum class EventType
{
	None,
	// Keyboard
	KeyPressed, KeyReleased,
	// Player Move
	W, S, A, D,
	// Bullet Shooting
	Shooting,
	//PlayerDamage
	getDamage,
	// Sounds
	PlayGunSound,
	// Score
	EnemyDestoryed,
	// Application
	LoadLevel, Quit
};


class Event
{
public:
	Event(EventType e_type);
	
	~Event() {}

	// The GetEventType gets event in every subsystem's HandlEvent() functions
	inline EventType GetEventType() { return m_eType; }
private:
	// Event type
	EventType m_eType{ EventType::None };

};

