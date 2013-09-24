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
	   XSILIUM_ZONE,
	   XSILIUM_ALL
};

enum Opcode
{
	// partie generique
	ID_CONNEXION = 0,
	ID_DECONEXION,

	// partie authentification
	ID_AUTH,

    //partie royaume
    ID_CHAT,

    //partie ticket
    ID_TICKET,

    //Partie message
    ID_MAIL,

    ID_ALL
};


#endif /* OPCODE_H_ */
