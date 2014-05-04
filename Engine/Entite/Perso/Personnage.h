/*
 * \file Personnage.h
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef PERSONNAGE_H_
#define PERSONNAGE_H_

#include "Entite/Entite.h"


/*
 *
 */
class Personnage : public Entite {
public:
	Personnage(Ogre::SceneManager* sceneMgr,const char * nom,const char * fileMesh);
	virtual ~Personnage();

	void update(double timeSinceLastFrame);

	void processAnimation(Event * event);


};

#endif /* PERSONNAGE_H_ */
