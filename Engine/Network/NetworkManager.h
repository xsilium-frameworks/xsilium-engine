/*
 * \file NetworkManager.h
 *
 *  Created on: \date 6 oct. 2012
 *      Author: \author joda
 *  \brief :
 */

#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

#include <boost/thread.hpp>
#include "enet/enet.h"
#include "Singleton/Singleton.h"
#include "Callback/Callback.h"
#include "Opcode/Opcode.h"
#include "StructurePacket/StructureGeneral.h"

/*
 *
 */
class NetworkManager : public xsilium::Singleton<NetworkManager>, public Callback {

	friend class xsilium::Singleton<NetworkManager>;

public:
	NetworkManager();
	virtual ~NetworkManager();

	bool createConnexion();

	int connexionToHost(std::string url,int port);


	bool disconnexion();

	ENetEvent * getPacket();

	ENetHost * getClient();

	void deletePacket(ENetPacket * packet);

	void sendPacket( ENetPacket * packet, enet_uint8 channel = 0);

	bool isConnected();

private:

	static void * threadConnexion(void * arguments);

	bool endThread;
	bool isConnectedflag;

	boost::thread thread;
	ENetAddress address;
	ENetHost * client;
	ENetEvent eventClient;
	ENetEvent * packet;
	ENetPeer *peer;

	boost::mutex mutexSend;
	boost::mutex mutexDelete;



};

#endif /* NETWORKMANAGER_H_ */
