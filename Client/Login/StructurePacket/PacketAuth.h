/*
 * \file PacketAuth.h
 *
 *  Created on: \date 22 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#ifndef PACKETAUTH_H_
#define PACKETAUTH_H_

#include "Network/StructurePacket/StructureGeneral.h"

struct AUTHPACKET_TYPE
{
	structure_opcodeT structure_opcode;
	uint8_t           typeAuth;
};

struct AUTHPACKET_LC_C
{
	AUTHPACKET_TYPE authTypePacket;
	uint16_t  build;
	uint8_t   platform[4];
	uint8_t   os[4];
	uint8_t   country[4];
	uint8_t   login_len;
	char   login[64];
};

struct AUTHPACKET_ERROR
{
	AUTHPACKET_TYPE authTypePacket;
	uint8_t   errorID; /*!< correspond a l'erreur qui a ete detecter */
};


struct AUTHPACKET_LC_S
{
	AUTHPACKET_TYPE authTypePacket;
	uint32_t	key;
	uint32_t	key2;
};

struct AUTHPACKET_P_C
{
	AUTHPACKET_TYPE authTypePacket;
    char   A[32];

};

struct AUTHPACKET_P_S
{
	AUTHPACKET_TYPE authTypePacket;
    uint8_t   Key[20];
};





#endif /* PACKETAUTH_H_ */
