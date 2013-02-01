#ifndef JEUX_STATE_H
#define JEUX_STATE_H

#include "GameState/GameState.h"

#include"Console/Console.h"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include <OgreImage.h>

class DotSceneLoader;

enum QueryFlags
{
	OGRE_HEAD_MASK	= 1<<0,
    CUBE_MASK		= 1<<1
};

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

	Ogre::RaySceneQuery*		m_pRSQ;
	Ogre::SceneNode*			m_pCurrentObject;
	Ogre::Entity*				m_pCurrentEntity;

	InputManager * inputManager;

    std::vector<Ogre::String> 	mCamNames;
    void 						switchCamera(int idx);


    Ogre::TerrainGroup* 		mTerrainGroup;
    Ogre::TerrainGlobalOptions* mTerrainGlobals;
    bool 						mTerrainsImported;

    void 						defineTerrain(long x, long y);
    void 						initBlendMaps(Ogre::Terrain* terrain);
    void 						configureTerrainDefaults(Ogre::Light* light);

    DotSceneLoader* 			m_Loader;

	bool						m_bLMouseDown, m_bRMouseDown;


};



#endif
