#include "EventHandler.h"

std::vector<Event*> EventHandler::Event_Container;


void EventHandler::AddEvent(Event* event)
{
	Event_Container.push_back(event);
}

std::vector<Event*> EventHandler::GetEvents()
{
	return Event_Container;
}

void EventHandler::ClearEvent()
{
	for (Event* event : Event_Container)
	{
		delete event;
	}
	Event_Container.clear();
	
}
