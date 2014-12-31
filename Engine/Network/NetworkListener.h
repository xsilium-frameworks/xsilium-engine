/*
 * \file NetworkListener.h
 *
 *  Created on: \date 4 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef NETWORKLISTENER_H_
#define NETWORKLISTENER_H_

#include "Network/Opcode/Opcode.h"
#include <boost/thread.hpp>

#include "MessagePacket.h"

#include <queue>

namespace Engine {

#define NUM_THREAD_MODULE 1

/*
 *
 */
class NetworkListener {
public:
	NetworkListener();
	virtual ~NetworkListener();

	void run();

	void stopThread();

	virtual void processPacket(MessagePacket * messagePacket) = 0;

	void setPacket(MessagePacket * messagePacket);
	MessagePacket * getPacket();

	bool isEmpty();

protected:

	static void threadProcess(void * arguments);


	boost::condition_variable condition_Queue;
	boost::thread_group groupThread;
	bool endThread;

private:
	std::queue<MessagePacket*> ListOfPacket;
	boost::mutex mutexList;
};

} /* namespace Engine */

#endif /* NETWORKLISTENER_H_ */
