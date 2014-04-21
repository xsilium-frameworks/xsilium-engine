/*
 * \file ModuleActif.cpp
 *
 *  Created on: \date 6 avr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "ModuleActif.h"

ModuleActif::ModuleActif() {
	this->networkManager = NetworkManager::getInstance();
	endThread = false;
}

ModuleActif::~ModuleActif() {
	stopThread();
	while(!ListOfPacket.empty())
		ListOfPacket.pop();
}

void ModuleActif::run()
{
	for(uint8_t i = 0;i< NUM_THREAD_MODULE;i++)
	{
		groupThread.add_thread(new boost::thread(&ModuleActif::threadProcess, (void *) this) );
	}
}

void ModuleActif::stopThread()
{
	endThread = true;
	condition_Queue.notify_all();
	groupThread.join_all();
}


ENetEvent ModuleActif::getPacket()
{
	boost::unique_lock<boost::mutex> lock(mutexList);
	ENetEvent  packet = ListOfPacket.front();
	ListOfPacket.pop();
	return packet;
}

void ModuleActif::setPacket()
{
	boost::unique_lock<boost::mutex> lock(mutexList);

	ListOfPacket.push(*(networkManager->getPacket()));
	lock.unlock();
	condition_Queue.notify_one();
}

bool ModuleActif::isEmpty()
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

void ModuleActif::threadProcess(void * arguments)
{
	ModuleActif * moduleActif = (ModuleActif *) arguments ;

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
