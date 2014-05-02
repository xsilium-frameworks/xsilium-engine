/*
 * \file Objet.h
 *
 *  Created on: \date 2 mai 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef OBJET_H_
#define OBJET_H_


#include <string>
#include <stdint.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>

/*
 *
 */
class Objet {
public:
	Objet(Ogre::SceneManager* sceneMgr,const char * nomObjet,const char * fileMesh);
	virtual ~Objet();

	void setNom(const char * nom);
	std::string * getNom();

	void setType(int typeObjet);
	int getType();

	Ogre::Entity* getObjet();

	void update(double timeSinceLastFrame);


private:

	int usure ;
	std::string * nom;

	Ogre::Entity* objetEnt;
	Ogre::SceneManager* sceneMgr;

	int typeObjet;

};

#endif /* OBJET_H_ */
