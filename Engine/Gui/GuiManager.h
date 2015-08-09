/*
 * \file GuiManager.h
 *
 *  Created on: \date 26 ao�t 2014
 *      Author: \author xelfe joda
 *  \brief : Fichier d'en-t�te du gestionnaire d'interface GUI
 */
#ifndef GUIMANAGER_H_
#define GUIMANAGER_H_

#ifdef WIN32
#define interface QQInterface
#endif

#include "GuiInput.h"
#include "GuiListenner.h"


/*!
 * \namespace Engine
 * \brief Espace de nommage regroupant les dff�rentes classes du moteur.
 */
namespace Engine {

class GuiListenner;

/*!
 * \class GuiManager
 * \brief Classe gestionnaire d'interface GUI.
 *
 * Classe permettant de g�rer les diff�rentes interface graphique.
 *
 */
class GuiManager: public Singleton<GuiManager>,
public EventListener,
public Ogre::FrameListener {

	friend class Singleton<GuiManager> ;

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
	 * \brief Application d'�vennements.
	 *
	 * initialisation du guiManager
	 *
	 */
	void init(Ogre::Root* m_pRoot);

	/*!
	 * \brief Application d'�vennements.
	 *
	 * Proc�de � l'�vennement si il existe
	 *
	 * \param event Instance d'�vennement pass� en param�tre par le client
	 *
	 */
	void processEvent(Event* event);

	/*!
	 * \brief Methode avant le chargement d'un frame
	 *
	 * \praram m_FrameEvent Instance de la constante Ogre::FrameEvent
	 *
	 * \return true si appell�
	 */
	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);

	/*!
	 * \brief Methode apr�s le chargement de tous les frames
	 *
	 * M�thode qui est charg� quand tous les �vennements par frame � �t� appeller.
	 *
	 * \praram m_FrameEvent Instance de la constante Ogre::FrameEvent
	 *
	 * \return true si appell�
	 */
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);

	/*!
	 * \brief Methode apr�s le chargement d'un frame
	 *
	 * \praram m_FrameEvent Instance de la constante Ogre::FrameEvent
	 *
	 * \return true si appell�
	 */
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

	/*!
	 * \brief Methode de configuration du theme GUI
	 *
	 * \praram event Instance d'evennement pass� en param�tre par le client
	 *
	 */
	void setTheme(Event* event);

	/*!
	 * \brief Methode de configuration du theme GUI
	 *
	 * \praram
	 *
	 */
	void setTheme(Ogre::String theme);

	/*!
	 * \brief Methode accesseur au nom du theme
	 *
	 * \return string nom du theme.
	 *
	 */
	std::string getTheme();

	/*!
	 * \brief M�thode de chargement de l'interface principale GUI
	 *
	 */
	void interfacePrincipal();

	/*!
	 * \brief M�thode de destruction de l'interface principale GUI
	 *
	 */
	void deleteInterfacePrincipal();

	/*!
	 * \brief M�thode de destruction de l'interface principale GUI
	 *
	 */
	void loadRessource();

	void addGuiListenner(GuiListenner* guiListenner);
	void removeGuiListenner(GuiListenner* guiListenner);

private:
	Ogre::String theme; /*!< Nom du theme configur�. */
	GuiInput* guiInput;
	bool interfacePrincipale; /*!< R�sultat d�signant si interfacePrincpale() � �t� initialis�. */
	CEGUI::OgreRenderer * mRenderer;
	Ogre::Root* m_pRoot;

	std::vector<GuiListenner*> listOfInterface;
};

} /* namespace Engine */

#endif /* GUIMANAGER_H_ */
