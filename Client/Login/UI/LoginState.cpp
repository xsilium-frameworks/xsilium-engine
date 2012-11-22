#include "LoginState.h"
//#include "DialogSystem.h"


using namespace Ogre;

LoginState::LoginState()
{
    m_bQuit         = false;
    m_FrameEvent    = Ogre::FrameEvent();
    auth = new Authentification();
    messageFlag = false;

}

void LoginState::enter()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering LoginState...");
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

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "LoginSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("MenuCam");
    m_pCamera->setPosition(Vector3(0, 50, 100));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);


    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

    createScene();
    auth->InitialisationAuth();
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
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving LoginState...");

    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);

    CEGUI::WindowManager::getSingleton().destroyAllWindows();


}

bool LoginState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        m_bQuit = true;
        return true;
    }
    CEGUI::System& gui_system(CEGUI::System::getSingleton());


     // do event injection
     CEGUI::GUIContext& ctx = CEGUI::System::getSingleton().getDefaultGUIContext();

     // key down
     ctx.injectKeyDown(static_cast<CEGUI::Key::Scan>(keyEventRef.key));

     // now character
     ctx.injectChar(keyEventRef.text);
    OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}

bool LoginState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().
        injectKeyUp(static_cast<CEGUI::Key::Scan>(keyEventRef.key));
    OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
    return true;
}

bool LoginState::mouseMoved(const OIS::MouseEvent &evt)
{
	CEGUI::GUIContext& ctx = CEGUI::System::getSingleton().getDefaultGUIContext();

	   ctx.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
	   ctx.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
    return true;
}

bool LoginState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().
        injectMouseButtonDown(convertOISButtonToCegui(id));
    return true;
}

bool LoginState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().
        injectMouseButtonUp(convertOISButtonToCegui(id));
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
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Click PushConnexion!!!");



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

void LoginState::setMessage(int message)
{
	if (messageFlag == false)
	{
		messageFlag = true;
		switch (message)
		    {
		        case 0:
		        	popupLogin->getChild("lblMessage")->setText("Identification réussie");
		            break;

		        case 1:
		        	popupLogin->getChild("lblMessage")->setText("Déconnexion réussie");
		            break;

		        case 2:
		        	popupLogin->getChild("lblMessage")->setText("Envoie du nom utilisateur");
		            break;

		        case 3:
		        	popupLogin->getChild("lblMessage")->setText("Vérification de sécurité");
		            break;

		        case 4:
		        	popupLogin->getChild("lblMessage")->setText("Envoie de sécurité");
		            break;

		        case 5:
		        	popupLogin->getChild("lblMessage")->setText("Envois de validation");
		            break;

		        case 6:
		        	popupLogin->getChild("lblMessage")->setText("Réception des royaumes");
		            break;

		        case 7:
		     		popupLogin->getChild("lblMessage")->setText("Demande de royaume");
		     		break;

		        case 8:
		        	popupLogin->getChild("lblMessage")->setText("Connexion bannie");
		        	break;

		        case 9:
		        	popupLogin->getChild("lblMessage")->setText("Compte banni");
		        	break;

		        case 10:
		        	popupLogin->getChild("lblMessage")->setText("Mauvais mot de passe");
		        	break;

		        case 11:
		        	popupLogin->getChild("lblMessage")->setText("Compte innexistant");
		        	break;

		        case 12:
		        	popupLogin->getChild("lblMessage")->setText("Envoie du nom utilisateur");
		        	break;

		        case 13:
		        	popupLogin->getChild("lblMessage")->setText("Envoie du nom utilisateur");
		        	break;

		        case 14:
		        	popupLogin->getChild("lblMessage")->setText("Envoie du nom utilisateur");
		        	break;

		        case 15:
		        	popupLogin->getChild("lblMessage")->setText("Envoie du nom utilisateur");
		        	break;

		        case 16:
		        	popupLogin->getChild("lblMessage")->setText("Envoie du nom utilisateur");
		        	break;

		        default:
		        	popupLogin->getChild("lblMessage")->setText("Erreur inconnue");

		            break;
		    }
	}
}


CEGUI::MouseButton LoginState::convertOISButtonToCegui(int buttonID)
{
   using namespace OIS;

   switch (buttonID)
    {
   case OIS::MB_Left:
        return CEGUI::LeftButton;
   case OIS::MB_Right:
        return CEGUI::RightButton;
   case OIS::MB_Middle:
        return CEGUI::MiddleButton;
    default:
        return CEGUI::LeftButton;
    }


}





