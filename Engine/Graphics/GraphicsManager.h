/*
 * \file GraphicsManager.h
 *
 *  Created on: \date 26 ao�t 2014
 *      Author: \author xelfe joda
 *  \brief : Fichier d'en-t�te de la classe GraphicsManager
 */
#ifndef GRAPHICSMANAGER_H_
#define GRAPHICSMANAGER_H_

#include <Engine/Engine.h>
#include "GraphicsEntiteManager.h"
#include "GraphicsSceneLoader.h"
#include "GraphicsCamera.h"
#include "GraphicsMouvementManager.h"
#include "GraphicsObjetManager.h"
#include "GraphicsMeteoManager.h"

#include <Input/InputManager.h>

#include <Physics/PhysicsManager.h>

namespace Engine {

	/*
	 *
	 */
	class GraphicsManager : public Singleton<GraphicsManager>, public EngineListenner, public Ogre::FrameListener {

		friend class Singleton < GraphicsManager > ;
	public:
		GraphicsManager();
		virtual ~GraphicsManager();

		void initOgre();

		void setParamettreOgre(Ogre::String key, Ogre::String valeur);

		void createWindow();
		void exit();

		void loadRessource();

		void loadScene(Event* event);

		Ogre::RenderWindow* getRenderWindow();

		void processEvent(Event* event);

		bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
		bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
		bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

	private:
		Ogre::String				m_SceneFile;

		Ogre::String				mResourcePath;

		Ogre::RenderSystem*			m_pRenderSystem;
		Ogre::RenderWindow*			m_pRenderWnd;
		Ogre::Root*					m_pRoot;
		Ogre::SceneManager*			m_pSceneMgr;
		Ogre::Camera* 				m_pCamera;

		Ogre::String				fenetreName;
		bool						sauvegardeParam;

		GraphicsEntiteManager*		graphicsEntiteManager;
		GraphicsSceneLoader*		graphicsSceneLoader;
		InputManager*				inputManager;
		GraphicsCamera*				graphicsCamera;
		GraphicsMouvementManager *  graphicsMouvementManager;
		GraphicsMeteoManager * graphicsMeteoManager;

	};

} /* namespace Engine */

#endif /* GRAPHICSMANAGER_H_ */
