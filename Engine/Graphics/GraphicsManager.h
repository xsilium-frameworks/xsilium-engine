/*
 * \file GraphicsManager.h
 *
 *  Created on: \date 26 ao�t 2014
 *      Author: \author xelfe joda
 *  \brief : Fichier d'en-t�te de la classe GraphicsManager
 */
#ifndef GRAPHICSMANAGER_H_
#define GRAPHICSMANAGER_H_

#include "GraphicsEntiteManager.h"
#include "GraphicsSceneLoader.h"
#include "GraphicsMouvementManager.h"
#include "GraphicsMeteoManager.h"

namespace Engine {

	/*
	 *
	 */
	class GraphicsManager : public Singleton<GraphicsManager>, public EventListener, public Ogre::FrameListener {

		friend class Singleton < GraphicsManager > ;
	public:
		GraphicsManager();
		virtual ~GraphicsManager();

		void init(std::string mResourcePath,std::string configFile);

		void setParamettreOgre(Ogre::String key, Ogre::String valeur);

		void createWindow();
		void exit();

		void loadRessource(std::string mResourcePath,std::string ressourceFile);

		void loadScene(Event* event);

		Ogre::RenderWindow* getRenderWindow();

		void processEvent(Event* event);

		bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
		bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
		bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);

		Ogre::Root* getRoot();


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
