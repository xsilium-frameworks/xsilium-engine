/*
 * \file EventManager.cpp
 *
 *  Created on: \date 10 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#include "EventManager.h"

namespace Engine {

EventManager::EventManager() {
	// TODO Auto-generated constructor stub

}

EventManager::~EventManager() {
	while(!listOfEvent.empty() )
		listOfEvent.pop_front();
}

void EventManager::addEvent(Event event)
{
	boost::unique_lock<boost::mutex> lock(mutexList);

	listOfEvent.push_back(event);

}

void EventManager::removeEvent()
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	listOfEvent.pop_front();
}

Event * EventManager::getEvent()
{
	boost::unique_lock<boost::mutex> lock(mutexList, boost::defer_lock);
	if(lock.try_lock())
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

} /* namespace Engine */
