/*
 * \file ControleInterface.h
 *
 *  Created on: \date 4 nov. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef CONTROLEINTERFACE_H_
#define CONTROLEINTERFACE_H_

#include "string.h"

/*
 *
 */
class ControleInterface {
public:
	ControleInterface();
	virtual ~ControleInterface();

	virtual void retourInterface(int IDInterface,int retour);
};

#endif /* CONTROLEINTERFACE_H_ */
