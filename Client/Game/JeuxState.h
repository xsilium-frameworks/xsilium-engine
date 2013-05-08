#ifndef JEUX_STATE_H
#define JEUX_STATE_H

#include "GameState/GameState.h"

#include"Chat/Interface/Chat.h"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include <OgreImage.h>


#include "PagedGeometry.h"
#include "GrassLoader.h"
#include "BatchPage.h"
#include "ImpostorPage.h"
#include "TreeLoader3D.h"

#include "GestionnaireMeteo/GestionnaireMeteo.h"

#include "Entite/Perso/Personnage.h"

class DotSceneLoader;

namespace Forests
{
    class PagedGeometry;
    class GrassLoader;
    class GrassLayer;
}

class JeuxState :public OIS::KeyListener,public OIS::MouseListener, public GameState
{
public:
	JeuxState();

	DECLARE_GAMESTATE_CLASS(JeuxState)

	void enter();
	void createScene();
	void exit();
	bool pause();
	void resume();

    void buildGUI();
//    void itemSelected(OgreBites::SelectMenu* menu);

	void update(double timeSinceLastFrame);

	void getInput();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

    bool mouseMoved( const OIS::MouseEvent &event );
    bool mousePressed( const OIS::MouseEvent &event, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &event, OIS::MouseButtonID id );

private:

	bool						m_bQuit;

	Ogre::Vector3				m_TranslateVector;
	Ogre::Real					m_MoveSpeed;
	Ogre::Degree				m_RotateSpeed;
	float						m_MoveScale;
	Ogre::Degree				m_RotScale;

	InputManager * inputManager;

    std::vector<Ogre::String> 	mCamNames;
    void 						switchCamera(int idx);


    Ogre::TerrainGroup* 		mTerrainGroup;
    bool 						m_TerrainImported;
    Ogre::String 				m_SceneFile;

    DotSceneLoader* 			m_Loader;

	bool						m_bLMouseDown, m_bRMouseDown;

    Forests::PagedGeometry* 	mPGHandle;                         /** Handle to Forests::PagedGeometry object */
    Forests::GrassLoader* 		mGrassLoaderHandle;                /** Handle to Forests::GrassLoader object */
    Forests::GrassLayer* 		mPGLayers[4];
    float* 						mPGLayerData[4];
    Ogre::Image 				mPGDensityMap;
    Ogre::Rect 					mPGDirtyRect;

    GestionnaireMeteo* gestionnaireMeteo;
    Chat * chat;
	KeyboardMap * keyboardMap ;

	Personnage * perso;



};



#endif
