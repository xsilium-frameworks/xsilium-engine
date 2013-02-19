/*
 * \file Opcode.h
 *
 *  Created on: \date 7 nov. 2012
 *      Author: \author joda
 *  \brief :
 */

#ifndef OPCODE_H_
#define OPCODE_H_

enum typerequete
{
	   XSILIUM_AUTH = 0,
	   XSILIUM_KINGDOM,
	   XSILIUM_ALL
};

enum Opcode
{
	ID_CONNEXION = 0,
	ID_DECONEXION,
    ID_SEND_USER,
    ID_SEND_CHALLENGE,
    ID_SEND_REPONSE,
    ID_SEND_VALIDATION,
    ID_GET_ROYAUME,
    ID_SEND_ROYAUME,
    ID_CONNECTION_BANNED,
    ID_INVALID_ACCOUNT_OR_PASSWORD,
    ID_COMPTE_BANNIE,
    ID_SEND_CANCEL,
    ID_INVALID_IP,
    ID_ERROR,

    //chat
    ID_CHAT,

    ID_OPCOD_MAX
};


#endif /* OPCODE_H_ */
