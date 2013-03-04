/*
 * \file NetworkManager.cpp
 *
 *  Created on: \date 6 oct. 2012
 *      Author: \author joda
 *  \brief :
 */

#include "Network/NetworkManager.h"

NetworkManager::NetworkManager() {
	enet_initialize();
	peer = NULL;
	createConnexion();
	isConnectedflag = false;
}

NetworkManager::~NetworkManager() {

	listOfListener.clear();
}

bool NetworkManager::isConnected()
{
	return isConnectedflag;
}

void NetworkManager::createConnexion()
{
	client = enet_host_create (NULL /* create a client host */,
	                1 /* only allow 1 outgoing connection */,
	                2 /* allow up 2 channels to be used, 0 and 1 */,
	                57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
	                14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);
}

int NetworkManager::connexionToHost(std::string url,int port)
{
	/* Connect to some.server.net:1234. */
	    enet_address_set_host (& address,url.c_str());
	    address.port = port;

	    /* Initiate the connection, allocating the two channels 0 and 1. */
	    peer = enet_host_connect (client, & address, 2, 0);

	    if (peer == NULL)
	    {
	       return 1;
	    }

	    /* Wait up to 5 seconds for the connection attempt to succeed. */
	    if (enet_host_service (client, &eventClient, 5000) > 0 && eventClient.type == ENET_EVENT_TYPE_CONNECT)
	    {
	    	isConnectedflag = true;
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

bool NetworkManager::sendToHost(const void * message,int sizeOfMessage)
{
	/* Create a reliable packet of size 7 containing "packet\0" */

	    ENetPacket * packet = enet_packet_create (message,sizeOfMessage,ENET_PACKET_FLAG_RELIABLE);
	    enet_peer_send (peer, 0, packet);

	    return true;

}

void* NetworkManager::threadConnexion(void* arguments)
{
	NetworkManager * networkManager = (NetworkManager *) arguments ;
	networkManager->packet = &networkManager->eventClient;

	while ((enet_host_service (networkManager->client,&networkManager->eventClient, 1000) >= 0 ) && (networkManager->isConnectedflag)  )
	{
		if(networkManager->eventClient.type >0)
		{
			networkManager->callBack(networkManager->eventClient.type);

			if (networkManager->eventClient.type == ENET_EVENT_TYPE_RECEIVE )
			{
				/* Clean up the packet now that we're done using it. */
				enet_packet_destroy (networkManager->eventClient.packet);
			}
		}

	}
	return NULL;
}

void NetworkManager::disconnexion()
{
	if(peer != NULL)
	{
		if(isConnectedflag)
		{
			isConnectedflag = false;
			thread.join();
		}
		enet_peer_disconnect (peer, 0);
	    /* Allow up to 3 seconds for the disconnect to succeed
	       and drop any packets received packets.
	     */
		while (enet_host_service (client, & eventClient, 3000) > 0)
		{
			switch (eventClient.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy (eventClient.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				puts ("Disconnection succeeded.");
				break;
			default:
				break;
			}
		}

		enet_peer_reset (peer);
	}

}

void NetworkManager::addNetworkListener( NetworkListener * networkListener, std::string instanceName ) {
	// Check for duplicate items
    listener = listOfListener.find( instanceName );
    if( listener == listOfListener.end() ) {
    	listOfListener[ instanceName ] = networkListener;
    }
}

bool NetworkManager::callBack(int event) {

	for (listener=listOfListener.begin() ; listener!=listOfListener.end() ; ++listener)
	{
			listener->second->updateNetwork(event,packet);
	}
    return true;
}

void NetworkManager::removeNetworkListener(std::string instanceName ) {
    // Check if item exists
    listener = listOfListener.find( instanceName );
    if( listener != listOfListener.end() ) {
    	listOfListener.erase( listener );
    }
}
