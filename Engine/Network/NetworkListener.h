/*
 * \file NetworkListener.h
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef NETWORKLISTENER_H_
#define NETWORKLISTENER_H_

#include "Network/NetworkManager.h"
#include "Network/Opcode/Opcode.h"

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

	virtual void processPacket(ENetEvent * packet) = 0;

	void setPacket();
	ENetEvent getPacket();

	bool isEmpty();

protected:

	static void threadProcess(void * arguments);


	boost::condition_variable condition_Queue;
	boost::thread_group groupThread;
	NetworkManager * networkManager;
	bool endThread;

private:
	std::queue<ENetEvent> ListOfPacket;
	boost::mutex mutexList;
};

} /* namespace Engine */

#endif /* NETWORKLISTENER_H_ */
