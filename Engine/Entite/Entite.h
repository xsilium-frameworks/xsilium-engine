/*
 * \file Entite.h
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef ENTITE_H_
#define ENTITE_H_

#include <map>

#include "Objet/Objet.h"
#include "Entite/GestionnaireAnimation/Animation.h"
#include "EventManager/EventManager.h"

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
	void degainerArme();
	bool isDegainerArme();

	void runAnimation();
	void idleAnimation();

	void update(double timeSinceLastFrame);

	void setEvent(Event event);

	virtual void processAnimation(Event * event) = 0;


	Ogre::SceneNode* getBody();

	void addObjet(const char * nomObjet,const char * fileMesh,const char * emplacement);



protected:
	int vieEntite;
	std::string * nom;

	uint8_t  charHeight ;
	int  runSpeed ;
	double  turnSpeed ;


	Ogre::SceneNode* mBodyNode;
	Ogre::Entity* mBodyEnt;

	Ogre::SceneManager* sceneMgr;

    EventManager * eventManager ;

	Animation * animation ;

	std::map<int,Objet*> listOfObject;
	int countObjet;

	bool degainer;


};

#endif /* ENTITE_H_ */
