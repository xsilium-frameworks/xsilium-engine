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

	virtual void run() = 0;

	virtual void stopThread() = 0;

	void setPacket();
	ENetEvent getPacket();

	bool isEmpty();

protected:
	boost::condition_variable condition_Queue;
	boost::thread_group groupThread;
	NetworkManager * networkManager;
	bool endThread;

private:
	std::queue<ENetEvent> ListOfPacket;
	boost::mutex mutexList;

};

#endif /* MODULEACTIF_H_ */
