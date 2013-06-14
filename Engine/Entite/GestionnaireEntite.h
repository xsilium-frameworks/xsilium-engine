/*
 * \file GestionnaireEntite.h
 *
 *  Created on: \date 13 juin 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GESTIONNAIREENTITE_H_
#define GESTIONNAIREENTITE_H_

#include <stdio.h>
#include <vector>

#include "Singleton/Singleton.h"

#include "Entite/Entite.h"

#include "XsiliumFramework.h"

/*
 *
 */
class GestionnaireEntite : public xsilium::Singleton<GestionnaireEntite> , public Ogre::FrameListener
{
	friend class xsilium::Singleton<GestionnaireEntite>;


public:
	GestionnaireEntite();
	virtual ~GestionnaireEntite();

	void ajouterEntite(Entite * entite);
	Entite * trouverEntite(std::string nom);


	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);



private:
	std::vector<Entite *> listOfEntite ;
    std::vector<Entite *>::iterator entite ;


};

#endif /* GESTIONNAIREENTITE_H_ */
