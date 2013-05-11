#include "JeuxState.h"


using namespace Ogre;
using namespace Forests;

JeuxState::JeuxState()
    :    m_Loader(0),
         m_TerrainImported(false),
         m_SceneFile(Ogre::StringUtil::BLANK)
{
    m_MoveSpeed			= 1.0f;
    m_RotateSpeed		= 0.3f;

    m_bQuit             = false;
    m_bLMouseDown = false;
    m_bRMouseDown = false;

    inputManager = InputManager::getSingletonPtr();
    keyboardMap = KeyboardMap::getInstance();

	interface = new Interface();
}


void JeuxState::enter()
{
    inputManager->addKeyListener(this,"Game1");


    XsiliumFramework::getInstance()->getLog()->logMessage("Entering JeuxState...");

    createScene();


    buildGUI();
}


bool JeuxState::pause()
{
    XsiliumFramework::getInstance()->getLog()->logMessage("Pausing JeuxState...");

    return true;
}


void JeuxState::resume()
{
    XsiliumFramework::getInstance()->getLog()->logMessage("Resuming JeuxState...");

    XsiliumFramework::getInstance()->getRenderWindow()->getViewport(0)->setCamera(m_pCamera);
    m_bQuit = false;
}

void JeuxState::exit()
{
    XsiliumFramework::getInstance()->getLog()->logMessage("Leaving JeuxState...");


    delete perso;

    delete chat;
    delete gestionnaireMeteo;
    interface->deleteInterfacePrincipal();

    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        XsiliumFramework::getInstance()->getRoot()->destroySceneManager(m_pSceneMgr);

    inputManager->removeKeyListener(this);
    delete interface;
}

void JeuxState::buildGUI()
{
	interface->interfacePrincipal();
    chat = new Chat();
}

void JeuxState::createScene()
{
	m_pSceneMgr = XsiliumFramework::getInstance()->getRoot()->createSceneManager(ST_GENERIC, "GameSceneMgr");

	m_Loader = new DotSceneLoader();
    m_Loader->parseDotScene("test-terrain.scene", "General", m_pSceneMgr);

    m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED);
    m_pSceneMgr->setShadowTextureConfig(0, 2048, 2048, Ogre::PF_X8R8G8B8);


    // Loop through all cameras and grab their name and set their debug representation

    m_pCamera = m_pSceneMgr->createCamera("PlayerCam");

    XsiliumFramework::getInstance()->getRenderWindow()->getViewport(0)->setCamera(m_pCamera);


     perso = new Personnage(m_pCamera);

     gestionnaireMeteo = new GestionnaireMeteo(m_pSceneMgr,m_pCamera,m_Loader->getSkyX());
     gestionnaireMeteo->create();

}

void JeuxState::update(double timeSinceLastFrame)
{
    CEGUI::System& gui_system(CEGUI::System::getSingleton());

    gui_system.injectTimePulse(timeSinceLastFrame);
    gui_system.getDefaultGUIContext().injectTimePulse(timeSinceLastFrame);

    if(m_bQuit == true)
    {
        popGameState();
        return;
    }


    chat->update();

    perso->update(timeSinceLastFrame);

}

bool JeuxState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	switch(keyEventRef.key)
	{
	case OIS::KC_ESCAPE:
		m_bQuit = true;
		break;
	case OIS::KC_LSHIFT:
			m_pCamera->moveRelative(m_TranslateVector);
		break;
	default:
		break;
	}
    return true;
}
bool JeuxState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	return true;
}


