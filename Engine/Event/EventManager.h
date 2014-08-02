/*
 * \file EventManager.h
 *
 *  Created on: \date 10 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include <deque>
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
	void removeEvent();
	Event * getEvent();


private:
	std::deque<Event> listOfEvent;

	boost::mutex mutexList;


};

} /* namespace Engine */

#endif /* EVENTMANAGER_H_ */
