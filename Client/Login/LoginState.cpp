#include "LoginState.h"


using namespace Ogre;

LoginState::LoginState()
{
	m_bQuit         = false;
	inputManager = InputManager::getSingletonPtr();
	m_FrameEvent    = Ogre::FrameEvent();
	interface = new Interface();
}

void LoginState::enter()
{
	XsiliumFramework::getInstance()->m_pLog->logMessage("Entering LoginState...");

	inputManager->addKeyListener(this,"Login");

	m_pSceneMgr = XsiliumFramework::getInstance()->m_pRoot->createSceneManager(ST_GENERIC, "LoginSceneMgr");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

	m_pCamera = m_pSceneMgr->createCamera("MenuCam");
	m_pCamera->setPosition(Vector3(0, 50, 100));
	m_pCamera->lookAt(Vector3(0, 0, 0));
	m_pCamera->setNearClipDistance(1);


	m_pCamera->setAspectRatio(Real(XsiliumFramework::getInstance()->m_pViewport->getActualWidth()) /
			Real(XsiliumFramework::getInstance()->m_pViewport->getActualHeight()));

	XsiliumFramework::getInstance()->m_pViewport->setCamera(m_pCamera);

	buildGUI();
	createScene();

	initialisationNetwork();

}

void LoginState::createScene()
{
	ParticleSystem* ps;
	ps = m_pSceneMgr->createParticleSystem("Nimbus", "Xsilium/GreenyNimbus");
	m_pSceneMgr->getRootSceneNode()->attachObject(ps);
}

void LoginState::buildGUI()
{
	interface->initialisationInterface();
	interface->interfacePrincipal();
	auth = new Authentification();
}

void LoginState::exit()
{
	XsiliumFramework::getInstance()->m_pLog->logMessage("Leaving LoginState...");

	m_pSceneMgr->destroyCamera(m_pCamera);

	inputManager->removeKeyListener(this);

	interface->deleteInterfacePrincipal();


	if(m_pSceneMgr)
		XsiliumFramework::getInstance()->m_pRoot->destroySceneManager(m_pSceneMgr);
	XsiliumFramework::getInstance()->m_pLog->logMessage("destruction scene...");

	delete auth;
	delete interface;

	NetworkManager::getInstance()->disconnexion();
}

bool LoginState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	switch(keyEventRef.key)
	{
	case OIS::KC_ESCAPE:
		m_bQuit = true;
		break;
	default:
		break;
	}

	return true;
}
bool LoginState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	return true;
}

void LoginState::initialisationNetwork()
{
	NetworkManager * networkManager = NetworkManager::getInstance();
	if (!networkManager->isConnected())
	{
		int messageErreur = networkManager->connexionToHost("85.25.251.97",60000);
		if( messageErreur == 1)
		{
			XsiliumFramework::getInstance()->m_pLog->logMessage("erreur de connexion : Le serveur est plein desoler ");
			auth->setEvent("0","Le serveur est plein desoler");
		}
		if( messageErreur == 2)
		{
			XsiliumFramework::getInstance()->m_pLog->logMessage("erreur de connexion : Impossible de se connecter au serveur");
			auth->setEvent("0","Impossible de se connecter au serveur");
		}
	}
}

void LoginState::update(double timeSinceLastFrame)
{
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;

	CEGUI::System& gui_system(CEGUI::System::getSingleton());

	gui_system.injectTimePulse(timeSinceLastFrame);
	gui_system.getDefaultGUIContext().injectTimePulse(timeSinceLastFrame);

	if(m_bQuit == true)
	{
		shutdown();
		return;
	}
	if(auth)
		auth->update();
}


