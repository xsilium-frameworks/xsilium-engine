/*
 * \file Opcode.h
 *
 *  Created on: \date 4 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef OPCODE_H_
#define OPCODE_H_

enum typerequete {
    XSILIUM_AUTH = 0, XSILIUM_KINGDOM, XSILIUM_ZONE, XSILIUM_ALL
};

enum Opcode {
    // partie generique

    ID_CONNEXION = 0,

    ID_DECONEXION,

    // partie authentification

    ID_AUTH,
    ID_ROYAUME,
    ID_ZONE,

    //partie royaume

    ID_CHAT,

    //partie ticket

    ID_TICKET,

    //Partie message

    ID_MAIL,

    ID_WORLD,

    ID_ALL
};

#endif /* OPCODE_H_ */
