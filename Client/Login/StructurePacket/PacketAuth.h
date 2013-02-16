/*
 * \file PacketAuth.h
 *
 *  Created on: \date 22 juin 2012
 *      Author: \author joda
 *  \brief :
 */

#ifndef PACKETAUTH_H_
#define PACKETAUTH_H_

#include "Shared/StructurePacket/StructurePacket.h"

	typedef struct AUTH_LOGON_CHALLENGE_C
	{
	    uint8_t   cmd;
	    uint8_t   opcode;
	    uint8_t   error;
	    uint16_t  size;
	    uint8_t   version1;
	    uint16_t  build;
	    uint8_t   platform[4];
	    uint8_t   os[4];
	    uint8_t   country[4];
	    uint32_t  timezone_bias;
	    uint8_t   login_len;
	    uint8_t   login[32];
	} sAuthLogonChallenge_C;


	typedef struct AUTH_LOGON_PROOF_C
	{
	    uint8_t   cmd;
	    uint8_t   opcode;
	    uint8_t   A[32];
	} sAuthLogonProof_C;

	typedef struct AUTH_LOGON_ERROR
	{
		uint8_t   cmd;
		uint8_t   opcode;
		uint8_t   error;
		uint8_t   M2[20];
	} sAuthLogonError;

	typedef struct AUTH_LOGON_CHALLENGE_S
	{
		uint8_t   cmd;  /*!< correspond au type de packet que l'on envoi */
		uint8_t   opcode;
		uint32_t	key;
		uint32_t	key2;
	} sAuthLogonChallenge_S;




#endif /* PACKETAUTH_H_ */
