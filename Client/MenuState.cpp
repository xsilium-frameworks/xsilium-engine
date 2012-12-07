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
    XsiliumFramework::getInstance()->m_pLog->logMessage("Entering MenuState...");
    CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());
   CEGUI::Window *sheet = winMgr.createWindow("DefaultWindow", "CEGUIApp/XsiliumMenu");

    m_pSceneMgr = XsiliumFramework::getInstance()->m_pRoot->createSceneManager(ST_GENERIC, "MenuSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("MenuCam");
    m_pCamera->setPosition(Vector3(0, 25, -50));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);

    m_pCamera->setAspectRatio(Real(XsiliumFramework::getInstance()->m_pViewport->getActualWidth()) /
        Real(XsiliumFramework::getInstance()->m_pViewport->getActualHeight()));

    XsiliumFramework::getInstance()->m_pViewport->setCamera(m_pCamera);

	/*
    XsiliumFramework::getInstance()->m_pTrayMgr->destroyAllWidgets();
    XsiliumFramework::getInstance()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    XsiliumFramework::getInstance()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    XsiliumFramework::getInstance()->m_pTrayMgr->showCursor();
    XsiliumFramework::getInstance()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "EnterBtn", "Enter GameState", 250);
    XsiliumFramework::getInstance()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ExitBtn", "Exit AdvancedXsiliumFramework", 250);
    XsiliumFramework::getInstance()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "MenuLbl", "Menu mode", 250);
*/

	
    createScene();
}

void MenuState::createScene()
{
}

void MenuState::exit()
{
    XsiliumFramework::getInstance()->m_pLog->logMessage("Leaving MenuState...");

    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        XsiliumFramework::getInstance()->m_pRoot->destroySceneManager(m_pSceneMgr);

//    XsiliumFramework::getInstance()->m_pTrayMgr->clearAllTrays();
//    XsiliumFramework::getInstance()->m_pTrayMgr->destroyAllWidgets();
//    XsiliumFramework::getInstance()->m_pTrayMgr->setListener(0);
}

void MenuState::update(double timeSinceLastFrame)
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
}

