/*
 * \file Engine.h
 *
 *  Created on: \date 2 aout 2014
 *      Author: \author joda
 *  \brief : Fichier d'en-tête de la classe Engine
 */
#ifndef ENGINE_H_
#define ENGINE_H_

#include <Graphics/GraphicsManager.h>
#include <Gui/GuiManager.h>
#include <Input/KeyboardManager.h>
#include <GameState/GameStateManager.h>

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
class Engine: public Singleton<Engine> , public EventListener {
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
	void initEngine(std::string configFile);

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
	std::string getResourcePath();

	Ogre::RenderWindow* getRenderWindow();

	void processEvent(Event* event);

private:

	std::string mResourcePath; /*!< Chemin vers les ressources */

	GuiManager* guiManager;
	GraphicsManager * graphicsManager;
	LogManager* logManager;
	EventManager * eventManager;

};

} /* namespace Engine */

#endif /* ENGINE_H_ */
