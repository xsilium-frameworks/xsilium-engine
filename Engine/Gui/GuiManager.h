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

		/*!
		* \brief Application d'évennements.
		*
		* Procède à l'évennement si il existe
		*
		* \param event Instance d'évennement passé en paramètre par le client
		*
		*/
		void processEvent(Event* event);

		/*!
		* \brief Méthode d'extinction
		*
		*/
		void shutdown();

		/*!
		* \brief Methode avant le chargement d'un frame
		*
		* \praram m_FrameEvent Instance de la constante Ogre::FrameEvent
		*
		* \return true si appellé
		*/
		bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);

		/*!
		* \brief Methode après le chargement de tous les frames
		*
		* Méthode qui est chargé quand tous les évennements par frame à été appeller.
		* 
		*
		* \praram m_FrameEvent Instance de la constante Ogre::FrameEvent
		*
		* \return true si appellé
		*/
		bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);

		/*!
		* \brief Methode après le chargement d'un frame
		*
		* \praram m_FrameEvent Instance de la constante Ogre::FrameEvent
		*
		* \return true si appellé
		*/
		bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

		/*!
		* \brief Methode de configuration du theme GUI
		*
		* \praram event Instance d'evennement passé en paramètre par le client
		*
		*/
		void setTheme(Event* event);

		/*!
		* \brief Méthode de chargement de l'interface principale GUI
		*
		*/
		void interfacePrincipal();

		/*!
		* \brief Méthode de destruction de l'interface principale GUI
		*
		*/
		void deleteInterfacePrincipal();

	private:
		bool interfacePrincipale; /*!< Résultat désignant si interfacePrincpale() à été initialisé. */
	};

} /* namespace Engine */

#endif /* GUIMANAGER_H_ */
