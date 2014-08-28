/*
 * \file GraphicsObjet.h
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSOBJET_H_
#define GRAPHICSOBJET_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>

namespace Engine {

/*
 *
 */
class GraphicsObjet {
public:
	GraphicsObjet();
	virtual ~GraphicsObjet();

	void initObjet(Ogre::SceneManager* sceneMgr,Ogre::String nom,Ogre::String fileMesh);

	Ogre::Entity* getObjet();
	Ogre::String* getNom();

	void setPosition(Ogre::Vector3 position);
	void setIndependant(bool seul);

	void update(double timeSinceLastFrame);

private:

	Ogre::String nom;
	Ogre::Entity* objetEnt;
	Ogre::SceneNode* objetNode;
	bool isIndependant;


};

} /* namespace Engine */

#endif /* GRAPHICSOBJET_H_ */
