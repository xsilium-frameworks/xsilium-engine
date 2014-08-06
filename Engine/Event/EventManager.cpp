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
	endThread = false;

}

EventManager::~EventManager() {
	while(!listOfEvent.empty() )
		listOfEvent.pop();
}

void EventManager::run(int nbThread)
{
	for(int i = 0;i< nbThread;i++)
	{
		groupThread.add_thread(new boost::thread(&EventManager::threadProcess, (void *) this) );
	}
}

void EventManager::stopThread()
{
	endThread = true;
	condition_Queue.notify_all();
	groupThread.join_all();
}

void EventManager::addEvent(Event event)
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	listOfEvent.push(event);
	lock.unlock();
	condition_Queue.notify_one();
}

Event  EventManager::getEvent()
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	Event event = listOfEvent.front();
	listOfEvent.pop();
	return event;

}

bool EventManager::isEmpty()
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	if(listOfEvent.empty())
	{
		condition_Queue.wait(lock);
		return true;
	}
	else
		return false;
}

void EventManager::threadProcess(void * arguments)
{
	EventManager * eventManager = (EventManager *) arguments ;

	while(!eventManager->endThread)
	{
		if(!eventManager->isEmpty())
		{
			Event event = eventManager->getEvent();
			eventManager->processEvent(&event);
		}
	}
}

} /* namespace Engine */
