/*
 * \file Engine.h
 *
 *  Created on: \date 2 aout 2014
 *      Author: \author joda
 *  \brief : Fichier d'en-tête de la classe Engine
 */
#ifndef ENGINE_H_
#define ENGINE_H_

#include "Singleton/Singleton.h"
#include "Event/Event.h"
#include "EngineListenner.h"
#include <vector>


#include <Ogre.h>
#include <OgreRoot.h>

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__
#include <Cocoa/Cocoa.h>
#endif

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE)
#include <OSX/macUtils.h>
#endif

/*! \namespace Engine
 *	\brief Espace de nommage regroupant les dfférentes classes du moteur
 *
 */
namespace Engine {

/*! \class Engine
 * \brief Classe d'initialisation des systèmes
 *
 *  Classe d'initialisation des systèmes fondamentaux du client
 *
 */
class Engine: public Singleton<Engine> {
	friend class Singleton<Engine> ;

public:
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Engine
	 *
	 */
	Engine();

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe Engine
	 *
	 */
	virtual ~Engine();

	/*!
	 *  \brief Méthode d'initialisation de configuration
	 *
	 *  \param[in] configFile : String du nom de fichier de configuration
	 *  \param[in] nbThread : int contenant le nombre de processus
	 */
	void initEngine(Ogre::String configFile, int nbThread);

	/*!
	 *  \brief Méthode d'initialisation de Ogre
	 *
	 *  \param[in] configFile : Ogre::String du nom de fichier de configuration
	 */
	void initOgre(Ogre::String configFile);

	/*!
	 *  \brief Méthode d'ajout d'écouteur
	 *
	 *  \param[in] engineListenner : Écouteur du moteur
	 */
	void addListenner(EngineListenner* engineListenner);

	/*!
	 *  \brief Méthode d'extinction des écouteurs du moteur
	 */
	void stopEngine();

	/*!
	 *  \brief Méthode de récupération de Ogre::Root
	 *
	 *	\return m_pRoot
	 */
	Ogre::Root* getRoot();

	/*!
	 *  \brief Méthode de récupération du chemin des ressources
	 *
	 *  \return mResourcePath
	 */
	Ogre::String * getResourcePath();

	/*!
	 *  \brief Méthode d'ajout d'évennement
	 *
	 *  \param event : Évennement à ajouter
	 */
	void addEvent(Event event);

	/*!
	 *  \brief Méthode de démarrage des images
	 *
	 *  \param m_FrameEvent : Structure contenant de l'information d'un évennement par image
	 */
	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);

	/*!
	 *  \brief Méthode de mise en attente des images
	 *
	 *  \param m_FrameEvent : Structure contenant de l'information d'un évennement par image
	 */
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);

	/*!
	 *  \brief Méthode de fin des images
	 *
	 *  \param m_FrameEvent : Structure contenant de l'information d'un évennement par image
	 */
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

private:

	Ogre::String mResourcePath; /*!< Chemin vers les ressources */
	Ogre::Root* m_pRoot; /*!< Instance de Ogre::root */

	std::vector<EngineListenner*> listOfEngineListenner; /*!< liste des écouteurs du moteur */

};

} /* namespace Engine */

#endif /* ENGINE_H_ */
