/*
 * \file GraphicsEntite.h
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSENTITE_H_
#define GRAPHICSENTITE_H_

#include <Ogre.h>
#include "GraphicsAnimation.h"

namespace Engine {

/*
 *
 */
class GraphicsEntite {
public:
	GraphicsEntite();
	virtual ~GraphicsEntite();

	void setNom(Ogre::String nom);
	void setCharHeight(int charHeight);
	void setRunSpeed(int runSpeed);
	void setTurnSpeed(double turnSpeed);

	void degainerArme();
	bool isDegainerArme();

	void update(double timeSinceLastFrame);

	void addEquipement(const char * nomObjet,const char * fileMesh,const char * emplacement);

private:
	Ogre::String  nom;

	int  charHeight ;
	int  runSpeed ;
	double  turnSpeed ;


	Ogre::SceneNode* mBodyNode;
	Ogre::Entity* mBodyEnt;

	GraphicsAnimation * graphicsAnimation ;

	//std::map<int,Objet*> listOfObject;
	int countObjet;


};

} /* namespace Engine */

#endif /* GRAPHICSENTITE_H_ */
