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

}

EventManager::~EventManager() {
	while(!listOfEvent.empty() )
		listOfEvent.pop();
}

void EventManager::addEvent(Event event)
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	listOfEvent.push(event);
}

Event * EventManager::getEvent()
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	return &listOfEvent.front();

}

void EventManager::deleteEvent()
{
	listOfEvent.pop();
}

bool EventManager::isEmpty()
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	if(listOfEvent.empty())
	{
		return true;
	}
	else
		return false;
}

} /* namespace Engine */
