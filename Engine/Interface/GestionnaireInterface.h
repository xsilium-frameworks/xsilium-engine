/*
 * \file GestionnaireInterface.h
 *
 *  Created on: \date 8 sept. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GESTIONNAIREINTERFACE_H_
#define GESTIONNAIREINTERFACE_H_

#include "Singleton/Singleton.h"
#include "Interface/Interface.h"

#include "XsiliumFramework.h"



/*
 *
 */
class GestionnaireInterface : public xsilium::Singleton<GestionnaireInterface> , public Ogre::FrameListener {

	friend class xsilium::Singleton<GestionnaireInterface>;

public:
	GestionnaireInterface();
	virtual ~GestionnaireInterface();

	void addInterface(GuiInterface * interface);
	void removeInterface(GuiInterface * interface);
	void removeAllInterface();
	bool findInterface(GuiInterface * interface);
	bool findWindow(CEGUI::Window* window);

    void initialisationInterface();
	void interfacePrincipal();
	void deleteInterfacePrincipal();

	bool onWindowActivated(const CEGUI::EventArgs &ea);
	bool onWindowDeactivated(const CEGUI::EventArgs &ea);

	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);



private:
	static void  threadAuthentification(void * arguments);

	std::vector<GuiInterface*> listOfInterfaceHistory;
	std::vector<GuiInterface*> listOfInterface;
	std::vector<GuiInterface*>::iterator interfaceIterator;


	bool interfacePrincipale;
};

#endif /* GESTIONNAIREINTERFACE_H_ */
