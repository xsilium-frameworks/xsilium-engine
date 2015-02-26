/*
 * \file NetworkListener.cpp
 *
 *  Created on: \date 4 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#include "NetworkListener.h"

namespace Engine {

NetworkListener::NetworkListener() {
	endThread = false;

}

NetworkListener::~NetworkListener() {
	stopThread();
	while(!ListOfPacket.empty())
		ListOfPacket.pop();
}

void NetworkListener::run()
{
	for(uint8_t i = 0;i< NUM_THREAD_MODULE;i++)
	{
		groupThread.add_thread(new boost::thread(&NetworkListener::threadProcess, (void *) this) );
	}
}

void NetworkListener::stopThread()
{
	endThread = true;
	condition_Queue.notify_all();
	groupThread.join_all();
}


MessagePacket* NetworkListener::getPacket()
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	MessagePacket * packet = ListOfPacket.front();
	ListOfPacket.pop();
	return packet;
}

void NetworkListener::setPacket(MessagePacket* messagePacket)
{
	boost::unique_lock<boost::mutex> lock(mutexList);

	ListOfPacket.push(messagePacket);
	lock.unlock();
	condition_Queue.notify_one();
}

bool NetworkListener::isEmpty()
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	if(ListOfPacket.empty())
	{
		condition_Queue.wait(lock);
		return true;
	}
	else
		return false;
}

void NetworkListener::threadProcess(void * arguments)
{
	NetworkListener * moduleActif = static_cast<NetworkListener *>( arguments ) ;

	while(!moduleActif->endThread)
	{
		if(!moduleActif->isEmpty())
		{
			MessagePacket * packet = moduleActif->getPacket();
			moduleActif->processPacket(packet);
            delete packet ;
		}
	}
}

} /* namespace Engine */
