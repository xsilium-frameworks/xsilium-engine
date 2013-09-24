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

	while(!ListOfPacket.empty())
		ListOfPacket.pop();
}

ENetEvent ModuleActif::getPacket()
{
	boost::mutex::scoped_lock lock(mutexList);
	ENetEvent  packet = ListOfPacket.front();
	ListOfPacket.pop();
	return packet;
}

void ModuleActif::setPacket()
{
	boost::mutex::scoped_lock lock(mutexList);

	ListOfPacket.push(*(networkManager->getPacket()));
	lock.unlock();
	condition_Queue.notify_one();
}

bool ModuleActif::isEmpty()
{
	boost::mutex::scoped_lock lock(mutexList);
	if(ListOfPacket.empty())
	{
		condition_Queue.wait(lock);
		return true;
	}
	else
		return false;
}
