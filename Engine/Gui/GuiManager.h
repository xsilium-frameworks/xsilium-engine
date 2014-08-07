/*
 * \file GuiManager.h
 *
 *  Created on: \date 7 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GUIMANAGER_H_
#define GUIMANAGER_H_

#ifdef WIN32
#define interface QQInterface
#endif

#include "Engine/Engine.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

namespace Engine {

/*
 *
 */
class GuiManager : public EngineListenner , public Ogre::FrameListener {
public:
	GuiManager();
	virtual ~GuiManager();

	void processEvent(Event * event);
	void shutdown();

	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

	void initialisationInterface();
	void interfacePrincipal();
	void deleteInterfacePrincipal();

private:
	bool interfacePrincipale;


};

} /* namespace Engine */

#endif /* GUIMANAGER_H_ */
