/*
 * \file NetworkManager.cpp
 *
 *  Created on: \date 3 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "NetworkManager.h"

namespace Engine {

NetworkManager::NetworkManager() {
	enet_initialize();
	peer = NULL;
	packet = NULL;
	client = NULL;
	isConnectedflag = false;
	endThread = false;
}

NetworkManager::~NetworkManager() {
    disconnexion();
	enet_deinitialize();
}

bool NetworkManager::isConnected()
{
	return isConnectedflag;
}

bool NetworkManager::createConnexion()
{
	client = enet_host_create (NULL /* create a client host */,
			1 /* only allow 1 outgoing connection */,
			2 /* allow up 2 channels to be used, 0 and 1 */,
			57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
			14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);
	if ( client != NULL)
	{
		enet_host_compress_with_range_coder(client);
		return true;
	}
	return false;
}

int NetworkManager::connexionToHost(std::string url,int port)
{
	enet_address_set_host (& address,url.c_str());
	address.port = port;
	peer = enet_host_connect (client, & address, 2, 0);
	if (peer == NULL)
	{
		return 1;
	}
	if (enet_host_service (client, &eventClient, 1000) > 0 && eventClient.type == ENET_EVENT_TYPE_CONNECT)
	{
		isConnectedflag = true;
		endThread = false;
		thread = boost::thread(&NetworkManager::threadConnexion, (void *) this);
		return 0;
	}
	else
	{
		/* Either the 5 seconds are up or a disconnect event was */
		/* received. Reset the peer in the event the 5 seconds   */
		/* had run out without any significant event.            */
		enet_peer_reset (peer);
		return 2 ;
	}
}

ENetEvent * NetworkManager::getPacket()
{
	return packet;
}

ENetHost * NetworkManager::getClient()
{
	return client;
}

void NetworkManager::deletePacket(ENetPacket * packet)
{
	boost::unique_lock<boost::mutex> lock(mutexDelete);
	enet_packet_destroy (packet);
}

void NetworkManager::sendPacket( ENetPacket * packet , enet_uint8 channel)
{
	boost::unique_lock<boost::mutex> lock(mutexSend);
	enet_peer_send(peer,channel,packet);
}

void* NetworkManager::threadConnexion(void* arguments)
{
	NetworkManager * networkManager = (NetworkManager *) arguments ;
	networkManager->packet = &networkManager->eventClient;

	while ((enet_host_service (networkManager->client,&networkManager->eventClient, 10) >= 0 ) && (networkManager->endThread == false )  )
	{
		switch (networkManager->eventClient.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			networkManager->callback((XSILIUM_ALL * 1000) + ID_CONNEXION);
			break;
		case ENET_EVENT_TYPE_RECEIVE:
		{
			structure_opcodeT * typePacket = (structure_opcodeT *) networkManager->eventClient.packet->data ;

			networkManager->callback( (typePacket->cmd * 1000 ) +  (typePacket->opcode ));

			break;
		}

		case ENET_EVENT_TYPE_DISCONNECT:
			networkManager->callback((XSILIUM_ALL * 1000 ) + ID_DECONEXION);
			networkManager->endThread = true;
			break;
		default:
			break;
		}
	}
	return NULL;
}

bool NetworkManager::disconnexion()
{
	if(peer != NULL)
	{
		if(isConnectedflag)
		{
			isConnectedflag = false;
		}
		enet_peer_disconnect (peer, 0);
		thread.join();
		enet_peer_reset (peer);
		return true;
	}
	return false;
}

} /* namespace Engine */
