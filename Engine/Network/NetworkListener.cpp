/*
 * \file NetworkListener.cpp
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "NetworkListener.h"

namespace Engine {

NetworkListener::NetworkListener() {
	this->networkManager = NetworkManager::getInstance();
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


ENetEvent NetworkListener::getPacket()
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	ENetEvent  packet = ListOfPacket.front();
	ListOfPacket.pop();
	return packet;
}

void NetworkListener::setPacket()
{
	boost::unique_lock<boost::mutex> lock(mutexList);

	ListOfPacket.push(*(networkManager->getPacket()));
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
			ENetEvent packet = moduleActif->getPacket();
			moduleActif->processPacket(&packet);
			moduleActif->networkManager->deletePacket(packet.packet);
		}
	}
}

} /* namespace Engine */
