#include "JeuxState.h"


using namespace Ogre;

JeuxState::JeuxState()
:    m_Loader(0)
{
	m_bQuit             = false;
	changeState = false;

	inputManager = InputManager::getSingletonPtr();
	keyboardMap = KeyboardMap::getInstance();
	gestionnaireChat = 0;
	gestionnaireEntite = 0;
	gestionnaireMouvement = 0;


}

JeuxState::~JeuxState()
{
}


void JeuxState::enter()
{
	inputManager->addKeyListener(this,"Game1");


	XsiliumFramework::getInstance()->getLog()->logMessage("Entering JeuxState...");

	GestionnaireInterface::getInstance()->interfacePrincipal();

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


	GestionnaireMouvement::DestroyInstance();
	delete gestionnaireEntite;

	delete gestionnaireChat;

	m_pSceneMgr->destroyCamera(m_pCamera);

	delete m_Loader;

	if(m_pSceneMgr)
		XsiliumFramework::getInstance()->getRoot()->destroySceneManager(m_pSceneMgr);

	inputManager->removeKeyListener(this);
}

void JeuxState::buildGUI()
{
	gestionnaireChat = new GestionnaireChat();
}

void JeuxState::createScene()
{
	m_pSceneMgr = XsiliumFramework::getInstance()->getRoot()->createSceneManager(ST_GENERIC, "GameSceneMgr");

	m_pCamera = m_pSceneMgr->createCamera("PlayerCam");
	m_pCamera->setNearClipDistance(0.1);

	XsiliumFramework::getInstance()->getRenderWindow()->getViewport(0)->setCamera(m_pCamera);


	m_Loader = new DotSceneLoader();
	m_Loader->parseDotScene("Xsilium1.scene", "General", m_pSceneMgr);
	gestionnaireEntite = new GestionnaireEntite();

	perso = new Personnage(m_pSceneMgr,"perso1","Sinbad.mesh");
	perso->addObjet("SinbadSword1", "Sword.mesh","Sheath.L");
	perso->addObjet("SinbadSword2", "Sword.mesh","Sheath.R");

	perso2 = new Personnage(m_pSceneMgr,"perso2","Sinbad.mesh");

	gestionnaireEntite->ajouterEntite(perso);
	gestionnaireEntite->ajouterEntite(perso2);

	gestionnaireMouvement = GestionnaireMouvement::getInstance();
	gestionnaireMouvement->setCamera(m_pCamera);
	gestionnaireMouvement->setEntities(perso);
	gestionnaireMouvement->activeDeplacement();

}

bool JeuxState::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent)
{
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
		setExit();
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


