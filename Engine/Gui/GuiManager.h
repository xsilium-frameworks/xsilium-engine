/*
 * \file GuiManager.h
 *
 *  Created on: \date 7 aožt 2014
 *      Author: \author joda
 *  \brief : Fichier d'en-tête du gestionnaire d'interface GUI
 */
#ifndef GUIMANAGER_H_
#define GUIMANAGER_H_

#ifdef WIN32
#define interface QQInterface
#endif

#include "Engine/Engine.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

/*!
 * \namespace Engine
 * \brief Espace de nommage regroupant les dfférentes classes du moteur.
 */
namespace Engine {

/*!
 * \class GuiManager
 * \brief Classe gestionnaire d'interface GUI.
 *
 * Classe permettant de gèrer les différentes interface graphique.
 *
 */
class GuiManager : public EngineListenner , public Ogre::FrameListener {
public:
		/*!
	 *  \brief Constructeur.
	 *
	 *  Constructeur de la classe GuiManager.
	 *
	 */
	GuiManager();
		/*!
	 *  \brief Destructeur.
	 *
	 *  Destructeur abstrait de la classe GuiManager.
	 *
	 */
	virtual ~GuiManager();

	void processEvent(Event* event);
	void shutdown();

	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);
	
    void setTheme(Event* event);
	void interfacePrincipal();
	void deleteInterfacePrincipal();

private:
	bool interfacePrincipale;
};

} /* namespace Engine */

#endif /* GUIMANAGER_H_ */
