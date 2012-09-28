#include "MenuState.h"
#include "CEGUI/CEGUI.h"


using namespace Ogre;

MenuState::MenuState()
{
    m_bQuit         = false;
    m_FrameEvent    = Ogre::FrameEvent();
}

void MenuState::enter()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering LoginState...");
    CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());
    CEGUI::Window *sheet = winMgr.createWindow("DefaultWindow", "CEGUIApp/XsiliumLogin");

    sheet->addChild(winMgr.loadLayoutFromFile("XsiliumLogin.layout"));



    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "MenuSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("MenuCam");
    m_pCamera->setPosition(Vector3(0, 25, -50));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);

    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

	/*
    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "EnterBtn", "Enter GameState", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ExitBtn", "Exit AdvancedOgreFramework", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "MenuLbl", "Menu mode", 250);
*/

	
    createScene();
}

void MenuState::createScene()
{
}

void MenuState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving MenuState...");

    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);

//    OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
//    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
//    OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);
}

bool MenuState::keyPressed(const OIS::KeyEvent &keyEventRef)
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

bool MenuState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().
        injectKeyUp(static_cast<CEGUI::Key::Scan>(keyEventRef.key));
    OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
    return true;
}

bool MenuState::mouseMoved(const OIS::MouseEvent &evt)
{
	CEGUI::GUIContext& ctx = CEGUI::System::getSingleton().getDefaultGUIContext();

	   ctx.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
	   ctx.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
    return true;
}

bool MenuState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
//    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    CEGUI::System::getSingleton().getDefaultGUIContext().
        injectMouseButtonDown(convertOISButtonToCegui(id));
    return true;
}

bool MenuState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
//    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    CEGUI::System::getSingleton().getDefaultGUIContext().
        injectMouseButtonUp(convertOISButtonToCegui(id));
    return true;
}

void MenuState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
//    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

    CEGUI::System& gui_system(CEGUI::System::getSingleton());

    gui_system.injectTimePulse(timeSinceLastFrame);
    gui_system.getDefaultGUIContext().injectTimePulse(timeSinceLastFrame);

    if(m_bQuit == true)
    {
        shutdown();
        return;
    }
}

CEGUI::MouseButton MenuState::convertOISButtonToCegui(int buttonID)
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

/*
void MenuState::buttonHit(OgreBites::Button *button)
{
    if(button->getName() == "ExitBtn")
        m_bQuit = true;
    else if(button->getName() == "EnterBtn")
        changeAppState(findByName("GameState"));
}
*/
