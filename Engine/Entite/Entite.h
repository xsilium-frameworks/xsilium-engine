/*
 * \file Entite.h
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef ENTITE_H_
#define ENTITE_H_

#include <string>
#include <stdint.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>

#include "Entite/GestionnaireAnimation/Animation.h"

/*
 *
 */
class Entite {
public:
	Entite();
	virtual ~Entite();

	void setVieEntite(int Vie);
	int getVieEntite();
	void setNom(const char * nom);
	std::string * getNom();
	double getTurnSpeed();
	int getRunSpeed();


	Ogre::SceneNode* getBody();



protected:
	int vieEntite;
	std::string * nom;

	uint8_t  charHeight ;
	int  runSpeed ;
	double  turnSpeed ;


	Ogre::SceneNode* mBodyNode;
	Ogre::Entity* mBodyEnt;

	Ogre::SceneManager* sceneMgr;


};

#endif /* ENTITE_H_ */
