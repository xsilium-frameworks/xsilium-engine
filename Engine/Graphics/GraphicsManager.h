/*
* \file GraphicsManager.h
*
*  Created on: \date 4 aožt 2014
*      Author: \author joda
*  \brief :
*/
#ifndef GRAPHICSMANAGER_H_
#define GRAPHICSMANAGER_H_

#include "Engine/Engine.h"
#include "Graphics/GraphicsEntiteManager.h"
#include "Graphics/GraphicsSceneLoader.h"
#include "Graphics/GraphicsCamera.h";
#include "Graphics/GraphicsMeteoManager.h"
#include "Input/InputManager.h"

namespace Engine {

	/*
	*
	*/
	class GraphicsManager : public EngineListenner , public Ogre::FrameListener , public OIS::KeyListener, public OIS::MouseListener {
	public:
		GraphicsManager();
		virtual ~GraphicsManager();

		void initOgre();

		void setParamettreOgre(Ogre::String key, Ogre::String valeur);

		void createWindow();

		void loadRessource();

		void loadScene(Event* event);

		Ogre::RenderWindow* getRenderWindow();

		void processEvent(Event* event);

		void shutdown();

		bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
		bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
		bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

		bool keyPressed( const OIS::KeyEvent &e );
		bool keyReleased( const OIS::KeyEvent &e );

		bool mouseMoved( const OIS::MouseEvent &e );
		bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
		bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

	private:
		Ogre::String m_SceneFile;

		Ogre::String mResourcePath ;

		Ogre::RenderSystem*			m_pRenderSystem;
		Ogre::RenderWindow*			m_pRenderWnd;
		Ogre::Root*					m_pRoot;
		Ogre::SceneManager*			m_pSceneMgr;

		Ogre::String fenetreName;
		bool sauvegardeParam;

	GraphicsEntiteManager * graphicsEntiteManager;
	GraphicsSceneLoader * graphicsSceneLoader;
	InputManager * inputManager;
	GraphicsCamera * graphicsCamera;
	GraphicsMeteoManager * graphicsMeteoManager;


	};

} /* namespace Engine */

#endif /* GRAPHICSMANAGER_H_ */
