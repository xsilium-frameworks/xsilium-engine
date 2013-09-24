#include "LoginState.h"


using namespace Ogre;

LoginState::LoginState()
{
	m_bQuit         = false;
	NetworkManager::getInstance();
	NetworkManager::getInstance()->createConnexion();
	gestionnaireAuth = new GestionnaireAuth(this);
}

LoginState::~LoginState()
{
	NetworkManager::DestroyInstance();
	delete gestionnaireAuth;
}
void LoginState::enter()
{
	XsiliumFramework::getInstance()->getLog()->logMessage("Entering LoginState...");

	m_pSceneMgr = XsiliumFramework::getInstance()->getRoot()->createSceneManager(ST_GENERIC, "LoginSceneMgr");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

	m_pCamera = m_pSceneMgr->createCamera("MenuCam");
	m_pCamera->setPosition(Vector3(0, 50, 100));
	m_pCamera->lookAt(Vector3(0, 0, 0));
	m_pCamera->setNearClipDistance(1);


	m_pCamera->setAspectRatio(Real(XsiliumFramework::getInstance()->getRenderWindow()->getViewport(0)->getActualWidth()) /
			Real(XsiliumFramework::getInstance()->getRenderWindow()->getViewport(0)->getActualHeight()));

	XsiliumFramework::getInstance()->getRenderWindow()->getViewport(0)->setCamera(m_pCamera);

	createScene();

}

void LoginState::createScene()
{
	ParticleSystem* ps;
	ps = m_pSceneMgr->createParticleSystem("Nimbus", "Xsilium/GreenyNimbus");
	m_pSceneMgr->getRootSceneNode()->attachObject(ps);
}

void LoginState::exit()
{
	XsiliumFramework::getInstance()->getLog()->logMessage("Leaving LoginState...");

	m_pSceneMgr->destroyCamera(m_pCamera);

	if(m_pSceneMgr)
		XsiliumFramework::getInstance()->getRoot()->destroySceneManager(m_pSceneMgr);
	XsiliumFramework::getInstance()->getLog()->logMessage("destruction scene...");

	NetworkManager::getInstance()->disconnexion();
}

void LoginState::setExit()
{
	m_bQuit = true;
}

bool LoginState::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent)
{
	CEGUI::System::getSingleton().injectTimePulse(m_FrameEvent.timeSinceLastFrame);

	if(m_bQuit == true)
	{
		popGameState();
		return false;
	}
	return true;
}


