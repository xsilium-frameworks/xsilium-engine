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

}

JeuxState::~JeuxState()
{
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



	delete gestionnaireEntite;

//	delete chat;
	delete gestionnaireMeteo;

	m_pSceneMgr->destroyCamera(m_pCamera);
	if(m_pSceneMgr)
		XsiliumFramework::getInstance()->getRoot()->destroySceneManager(m_pSceneMgr);

	inputManager->removeKeyListener(this);
}

void JeuxState::buildGUI()
{
	//chat = new Chat();
}

void JeuxState::createScene()
{
	m_pSceneMgr = XsiliumFramework::getInstance()->getRoot()->createSceneManager(ST_GENERIC, "GameSceneMgr");


	m_Loader = new DotSceneLoader();
	m_Loader->parseDotScene("basique_terrain1.scene", "General", m_pSceneMgr);


	// Light
	Ogre::Light *mLight0 = m_pSceneMgr->createLight("Light#0");
	mLight0->setDiffuseColour(1, 1, 1);
	mLight0->setCastShadows(false);

	m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED);
	m_pSceneMgr->setShadowTextureConfig(0, 2048, 2048, Ogre::PF_X8R8G8B8);

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);


	// Loop through all cameras and grab their name and set their debug representation

	m_pCamera = m_pSceneMgr->createCamera("PlayerCam");

	XsiliumFramework::getInstance()->getRenderWindow()->getViewport(0)->setCamera(m_pCamera);


	m_pCamera->setNearClipDistance(0.1);
	m_pCamera->setFarClipDistance(100);

	gestionnaireEntite = new GestionnaireEntite();

	perso = new Personnage(m_pSceneMgr,"perso1");

	perso2 = new Personnage(m_pSceneMgr,"perso2");

	gestionnaireEntite->ajouterEntite(perso);
	gestionnaireEntite->ajouterEntite(perso2);

	gestionnaireMouvement = new GestionnaireMouvement(m_pCamera);
	gestionnaireMouvement->setEntities(perso);

	gestionnaireMeteo = new GestionnaireMeteo(m_pSceneMgr,m_pCamera,m_Loader->getSkyX());
	gestionnaireMeteo->create();

}

bool JeuxState::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent)
{
	CEGUI::System& gui_system(CEGUI::System::getSingleton());

	gui_system.injectTimePulse(m_FrameEvent.timeSinceLastFrame);
	gui_system.getDefaultGUIContext().injectTimePulse(m_FrameEvent.timeSinceLastFrame);

	if(m_bQuit == true)
	{
		popGameState();
		return false;
	}

	return true;
}

bool JeuxState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	switch(keyEventRef.key)
	{
	case OIS::KC_ESCAPE:
		m_bQuit = true;
		break;
	case OIS::KC_LSHIFT:
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


