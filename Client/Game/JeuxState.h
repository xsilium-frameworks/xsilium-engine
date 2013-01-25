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
	virtual ~JeuxState(void);

	DECLARE_GAMESTATE_CLASS(JeuxState)

	void enter();
	void createScene();
	void exit();
	bool pause();
	void resume();

	void moveCamera();

//    void buildGUI();
//    void itemSelected(OgreBites::SelectMenu* menu);

	void update(double timeSinceLastFrame);

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
	bool						m_bSettingsMode;

	InputManager * inputManager;

    std::vector<Ogre::String> 	mCamNames;
    void 						switchCamera(int idx);
    Ogre::TerrainGroup* 		mTerrainGroup;
    DotSceneLoader* 			m_Loader;


};



#endif
