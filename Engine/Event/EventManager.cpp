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
	m_pRoot = 0;
}

EventManager::~EventManager() {
	m_pRoot->removeFrameListener(this);
	while(!listOfEvent.empty() )
		listOfEvent.pop();
}

void EventManager::init(Ogre::Root*	m_pRoot)
{
	this->m_pRoot = m_pRoot;
	m_pRoot->addFrameListener(this);
}

void EventManager::addEvent(Event event)
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	listOfEvent.push(event);
}

Event* EventManager::getEvent()
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

void EventManager::addListenneur(EventListener * eventListener)
{
	listOfEventListener.push_back(eventListener);
}


void EventManager::removeAllListenneur()
{
	listOfEventListener.clear();
}


void EventManager::callback(Event * event)
{
	std::vector<EventListener*>::iterator it;
	for (it=listOfEventListener.begin(); it<listOfEventListener.end(); ++it)
	{
		(*it)->processEvent(event);
	}
}

bool EventManager::frameStarted(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}
bool EventManager::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent)
{
	while(!isEmpty())
	{
		Event* event = getEvent();
		callback(event);
		deleteEvent();
	}
	return true;
}
bool EventManager::frameEnded(const Ogre::FrameEvent& m_FrameEvent)
{
	return true;
}

} /* namespace Engine */
