/*
 * \file ModuleActif.h
 *
 *  Created on: \date 6 avr. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef MODULEACTIF_H_
#define MODULEACTIF_H_

#include "Network/NetworkManager.h"
#include "Network/Opcode/Opcode.h"

#include <queue>
#include <boost/thread.hpp>

#define NUM_THREAD_MODULE 1

/*
 *
 */
class ModuleActif {
public:
	ModuleActif();
	virtual ~ModuleActif();

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

#endif /* MODULEACTIF_H_ */
