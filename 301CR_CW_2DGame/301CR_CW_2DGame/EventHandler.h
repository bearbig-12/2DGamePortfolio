#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Event.h"


// Event Handler must be only one because event handler get all of events in every subsystem.
// It can check event and call function to make event.
// if user make more than one instance, it will cause the problem. 
// Because of that, we need to make this class as Singletone 
class EventHandler
{
public:
	static void AddEvent(Event* event);
	static std::vector<Event*> GetEvents();
	static void ClearEvent();

private:
	static std::vector<Event*> Event_Container;

};

