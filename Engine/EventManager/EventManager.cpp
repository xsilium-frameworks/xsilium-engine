/*
 * \file EventManager.cpp
 *
 *  Created on: \date 10 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#include "EventManager.h"

EventManager::EventManager() {
	// TODO Auto-generated constructor stub

}

EventManager::~EventManager() {
	while(!listOfEvent.empty() )
		listOfEvent.pop_front();
}

void EventManager::addEvent(Event event)
{
	boost::mutex::scoped_lock lock(mutexList);

	listOfEvent.push_back(event);

}

void EventManager::removeEvent()
{
	boost::mutex::scoped_lock lock(mutexList);
	listOfEvent.pop_front();
}

Event * EventManager::getEvent()
{
	boost::mutex::scoped_try_lock lock(mutexList);
	if(lock)
	{
		if(!listOfEvent.empty())
			return &(listOfEvent.front());
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}
