/*
 * \file EventManager.h
 *
 *  Created on: \date 10 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include <queue>
#include <boost/thread/thread.hpp>
#include "Event.h"


namespace Engine {

/*
 *
 */

class EventManager {
public:
	EventManager();
	virtual ~EventManager();

	void addEvent(Event event);
	Event * getEvent();

	void deleteEvent();

	bool isEmpty();

	virtual void processEvent(Event * event) = 0;


private:
	std::queue<Event> listOfEvent;
	boost::mutex mutexList;


};

} /* namespace Engine */

#endif /* EVENTMANAGER_H_ */
