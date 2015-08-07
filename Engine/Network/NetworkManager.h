/*
 * \file NetworkManager.h
 *
 *  Created on: \date 3 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>


#include "enet/enet.h"
#include "Singleton/Singleton.h"
#include "Callback/Callback.h"
#include "Opcode/Opcode.h"
#include "NetworkListener.h"

namespace Engine {

/*
 *
 */
class NetworkManager : public Singleton<NetworkManager> {

	friend class Singleton<NetworkManager> ;


public:
	NetworkManager();
	virtual ~NetworkManager();

	bool createConnexion();

	int connexionToHost(std::string url,int port);


	bool disconnexion();

	void sendPacket( MessagePacket * messagePacket, enet_uint8 channel = 0);

	bool isConnected();

    void addlistenneur(int identifiant, NetworkListener * networkListener);
	void removelistenneur(int identifiant);
	void callback(int identifiant, MessagePacket * messagePacket = 0);

private:

	static void * threadConnexion(void * arguments);

	bool endThread;
	bool isConnectedflag;

	boost::thread thread;
	ENetAddress address;
	ENetHost * client;
	ENetEvent eventClient;
	ENetPeer *peer;

	boost::mutex mutexSend;

	std::map<int,NetworkListener* > listOfListenner ;
};

} /* namespace Engine */

#endif /* NETWORKMANAGER_H_ */
