/*
 * \file GestionnaireInterface.h
 *
 *  Created on: \date 8 sept. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GESTIONNAIREINTERFACE_H_
#define GESTIONNAIREINTERFACE_H_

#ifdef WIN32
#define interface QQInterface
#endif

#include "Singleton/Singleton.h"

#include "Interface/Interface.h"
#include "Interface/InputInterface.h"
#include "Interface/ControleInterface.h"
#include "XsiliumFramework.h"

/*
 *
 */
class GestionnaireInterface : public xsilium::Singleton<GestionnaireInterface> , public Ogre::FrameListener , public ControleInterface {

	friend class xsilium::Singleton<GestionnaireInterface>;

public:
	GestionnaireInterface();
	virtual ~GestionnaireInterface();

	void addInterface(GuiInterface * interface);
	void removeInterface(GuiInterface * interface);
	void removeAllInterface();
	bool findInterface(GuiInterface * interface);

	void addControleur(ControleInterface * controleInterface);
	void removeControleur(ControleInterface * controleInterface);
	bool findControleur(ControleInterface * controleInterface);

    void initialisationInterface();
	void interfacePrincipal();
	void deleteInterfacePrincipal();

	bool onWindowActivated(const CEGUI::EventArgs &ea);
	bool onWindowDeactivated(const CEGUI::EventArgs &ea);

	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

	void retourInterface(EventInterface eventInterface,int retour,ControleInterface * controleInterface);
	void retourInterface(EventInterface eventInterface,int retour)
	{
		retourInterface(eventInterface,retour,NULL);
	};


	void sendEvenement(EventInterface * eventInterface,Event * event);

private:

	std::vector<GuiInterface*> listOfInterface;
	std::vector<GuiInterface*>::iterator interfaceIterator;

	std::vector<ControleInterface *> listOfControleur;
	std::vector<ControleInterface *>::iterator controleurIterator;


	std::list<CEGUI::Window *> pWinHistory;

	InputInterface * inputInterface;
	bool interfacePrincipale;




};

#endif /* GESTIONNAIREINTERFACE_H_ */
