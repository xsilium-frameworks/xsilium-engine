/*
 * \file NetworkManager.h
 *
 *  Created on: \date 6 oct. 2012
 *      Author: \author joda
 *  \brief :
 */

#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

#include <pthread.h>
#include <map>
#include <string>

#include <enet/enet.h>
#include "Singleton/Singleton.h"
#include "NetworkListener.h"

/*
 *
 */
class NetworkManager : public Singleton<NetworkManager> {

	friend class Singleton<NetworkManager>;

public:
	NetworkManager();
	virtual ~NetworkManager();

	void createConnexion();
	int connexionToHost(std::string url,int port);
	bool sendToHost(const char * message,int sizeOfMessage);

	void disconnexion();

    bool callBack(int event);

    void addNetworkListener( NetworkListener * networkListener, std::string instanceName );
    void removeNetworkListener(std::string instanceName );

    bool isConnected();
protected:
	static void * threadConnexion(void * arguments);

private:
		bool endThread;

		pthread_t thread;
		ENetHost * client;
		ENetAddress address;
		ENetEvent eventClient;
		ENetEvent * packet;
		ENetPeer *peer;
		bool isConnectedflag;


	    std::map<std::string,NetworkListener *> listOfListener ;
	    std::map<std::string,NetworkListener *>::iterator listener ;


};

#endif /* NETWORKMANAGER_H_ */
