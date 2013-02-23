/*
 * \file PacketChat.h
 *
 *  Created on: \date 18 févr. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef PACKETCHAT_H_
#define PACKETCHAT_H_

#include "Shared/StructurePacket/StructurePacket.h"

typedef struct CHATPACKET_C
{
	structure_opcodeT structure_opcode;
    uint8_t        typeChat;
    char   perso[64];
    char   message[512];
} sChatPacket_C;



#endif /* PACKETCHAT_H_ */
