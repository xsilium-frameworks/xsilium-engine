/*
 * \file NetworkListener.h
 *
 *  Created on: \date 6 oct. 2012
 *      Author: \author joda
 *  \brief :
 */

#ifndef NETWORKLISTENER_H_
#define NETWORKLISTENER_H_
#include <stdio.h>

class NetworkListener
{
public:
	NetworkListener(){};
	virtual ~NetworkListener(){};

	virtual void updateNetwork(int event ,ENetEvent * packet) = 0;

};

#endif
