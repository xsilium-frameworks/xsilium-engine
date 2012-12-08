#include "LoginState.h"
//#include "DialogSystem.h"


using namespace Ogre;

LoginState::LoginState()
{
    m_bQuit         = false;
    inputManager = InputManager::getSingletonPtr();
    m_FrameEvent    = Ogre::FrameEvent();
    auth = new Authentification();
    messageFlag = false;

    inputManager->addKeyListener(this,"Login");

}

void LoginState::enter()
{
    XsiliumFramework::getInstance()->m_pLog->logMessage("Entering LoginState...");
    CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

    CEGUI::Window* base = winMgr.createWindow("DefaultWindow");

    CEGUI::Window* sheet = winMgr.loadLayoutFromFile("XsiliumLogin.layout");

    // attach this to the 'real' root
    base->addChild(sheet);

	frame = sheet->getChild("LoginForm");

	popupLogin = sheet->getChild("PopUp");

	popupLogin->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,CEGUI::Event::Subscriber(&LoginState::CloseButton, this));

	popupLogin->getChild("Button")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&LoginState::CloseButton, this));

	frame->getChild("edtUsername")->activate();
	frame->getChild("edtUsername")->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&LoginState::handleSubmit, this));


	frame->getChild("btnConnexion")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&LoginState::PushConnexion, this));



    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

    m_pSceneMgr = XsiliumFramework::getInstance()->m_pRoot->createSceneManager(ST_GENERIC, "LoginSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("MenuCam");
    m_pCamera->setPosition(Vector3(0, 50, 100));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);


    m_pCamera->setAspectRatio(Real(XsiliumFramework::getInstance()->m_pViewport->getActualWidth()) /
        Real(XsiliumFramework::getInstance()->m_pViewport->getActualHeight()));

    XsiliumFramework::getInstance()->m_pViewport->setCamera(m_pCamera);

    createScene();

    auth->setLogin(this);
}

void LoginState::createScene()
{
    ParticleSystem* ps;
    ps = m_pSceneMgr->createParticleSystem("Nimbus", "Xsilium/GreenyNimbus");
    		m_pSceneMgr->getRootSceneNode()->attachObject(ps);
}

void LoginState::exit()
{
	delete auth;
    XsiliumFramework::getInstance()->m_pLog->logMessage("Leaving LoginState...");

    m_pSceneMgr->destroyCamera(m_pCamera);

    if(m_pSceneMgr)
        XsiliumFramework::getInstance()->m_pRoot->destroySceneManager(m_pSceneMgr);
    XsiliumFramework::getInstance()->m_pLog->logMessage("destruction scene...");
//    CEGUI::WindowManager::getSingleton().destroyAllWindows();


}

bool LoginState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	switch(keyEventRef.key)
	{
	case OIS::KC_ESCAPE:
		m_bQuit = true;

		break;

	case OIS::KC_TAB:
		frame->getChild("edtPassword")->activate();
		break;
	case OIS::KC_RETURN:
		auth->setLoginPwd(frame->getChild("edtUsername")->getText().c_str(),frame->getChild("edtPassword")->getText().c_str());
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

    if ((messageFlag == true) && (!popupLogin->isActive()))
    {
    	frame->setAlpha(0.5);
    	popupLogin->setVisible("true");
    	popupLogin->activate();
    	popupLogin->setAlwaysOnTop(true);
    }
}


bool LoginState::PushConnexion(const CEGUI::EventArgs &e)
{
	XsiliumFramework::getInstance()->m_pLog->logMessage("Click PushConnexion!!!");

	auth->setLoginPwd(frame->getChild("edtUsername")->getText().c_str(),frame->getChild("edtPassword")->getText().c_str());
	return true;
}

bool LoginState::CloseButton(const CEGUI::EventArgs &e)
{
	messageFlag = false;
	popupLogin->setVisible(false);
	frame->setAlpha(1.0);
	frame->getChild("edtUsername")->activate();
	return true;

}

bool LoginState::handleSubmit(const CEGUI::EventArgs&)
{
    return true;
}

void LoginState::setMessage(int typeMessage ,int message)
{
	if (messageFlag == false)
	{
		messageFlag = true;
		switch (typeMessage)
		{
		case 0:
			switch (message)
					    {
							case 1:
								popupLogin->getChild("lblMessage")->setText("Les serveur est full dsl ");
								break;
					        case 2:
					        	popupLogin->getChild("lblMessage")->setText("Impossible de se connecter au serveur");
					            break;

					        case 3:
					        	popupLogin->getChild("lblMessage")->setText("Déconnexion réussie");
					            break;

					        default:
					        	popupLogin->getChild("lblMessage")->setText("Erreur inconnue");

					            break;
					    }
			break;
		case 1:
			switch (message)
								    {
										case ID_INVALID_ACCOUNT_OR_PASSWORD:
											popupLogin->getChild("lblMessage")->setText("Le login ou le mot de passe est incorrecte .");
											break;
								        case ID_CONNECTION_BANNED:
								        	popupLogin->getChild("lblMessage")->setText("Votre IP a ete banni .\n Il est imposible de se connecter .");
								            break;

								        case ID_COMPTE_BANNIE:
								        	popupLogin->getChild("lblMessage")->setText("Votre Compte a ete banni . \n Il est impossible de se connecter .");
								            break;
								        case ID_SEND_VALIDATION:
								        	popupLogin->getChild("lblMessage")->setText("Vous avez correctement ete authentifier .");
								        	changeAppState(findByName("GameState"));
								        	break;

								        default:
								        	popupLogin->getChild("lblMessage")->setText("Erreur inconnue");

								            break;
								    }
			break;
		}

	}
}




