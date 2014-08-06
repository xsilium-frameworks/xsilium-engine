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
	Event getEvent();

	bool isEmpty();

	void run(int nbThread);
	void stopThread();

	virtual void processEvent(Event * event) = 0;

protected:
	static void threadProcess(void * arguments);


private:
	std::queue<Event> listOfEvent;
	boost::condition_variable condition_Queue;
	boost::thread_group groupThread;
	boost::mutex mutexList;

	bool endThread;


};

} /* namespace Engine */

#endif /* EVENTMANAGER_H_ */
