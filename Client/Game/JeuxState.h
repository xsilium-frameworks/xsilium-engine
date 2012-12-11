#ifndef JEUX_STATE_H
#define JEUX_STATE_H

#include "GameState/GameState.h"

#include"Console/Console.h"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include <OgreImage.h>

#include "DotSceneLoader.h"

class DotSceneLoader;

namespace Forests
{
    class PagedGeometry;
    class GrassLoader;
    class GrassLayer;
}

class JeuxState :public OIS::KeyListener,public GameState
{
public:
	JeuxState();
	virtual ~JeuxState(void);

	DECLARE_GAMESTATE_CLASS(JeuxState)

	void enter();
	void createScene();
	void exit();
	bool pause();
	void resume();

	void moveCamera();
	void getInput();

//    void buildGUI();
//    void itemSelected(OgreBites::SelectMenu* menu);

	void update(double timeSinceLastFrame);

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

private:

	bool						m_bQuit;

	Ogre::Vector3				m_TranslateVector;
	Ogre::Real					m_MoveSpeed;
	Ogre::Degree				m_RotateSpeed;
	float						m_MoveScale;
	Ogre::Degree				m_RotScale;

	Ogre::RaySceneQuery*		m_pRSQ;
	Ogre::SceneNode*			m_pCurrentObject;
	Ogre::Entity*				m_pCurrentEntity;
	bool						m_bSettingsMode;

	InputManager * inputManager;

    std::vector<Ogre::String> 	mCamNames;
    void 						switchCamera(int idx);
    Ogre::TerrainGroup* 		mTerrainGroup;
    DotSceneLoader* 			m_Loader;
    bool 						m_TerrainImported;
    Ogre::String 				m_SceneFile;
 // Ogre::String 				mHelpInfo;
    bool 						m_Fly;
    Ogre::Real 					m_FallVelocity;

    Forests::PagedGeometry* 	mPGHandle;				/** Handle to Forests::PagedGeometry object */
    Forests::GrassLoader* 		mGrassLoaderHandle;     /** Handle to Forests::GrassLoader object */
    Forests::GrassLayer* 		mPGLayers[4];
    float* 						mPGLayerData[4];
    Ogre::Image 				mPGDensityMap;
    Ogre::Rect 					mPGDirtyRect;

};



#endif
