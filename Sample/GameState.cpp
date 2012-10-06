#include "GameState.h"

using namespace Ogre;

GameState::GameState()
{
    m_MoveSpeed			= 0.1f;
    m_RotateSpeed		= 0.3f;

    m_bLMouseDown       = false;
    m_bRMouseDown       = false;
    m_bQuit             = false;
    m_bSettingsMode     = false;

//    m_pDetailsPanel		= 0;
}

void GameState::enter()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");
    CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

    CEGUI::Window* base = winMgr.createWindow("DefaultWindow", "CEGUIApp/XsiliumGame");

    CEGUI::Window* sheet = winMgr.loadLayoutFromFile("XsiliumConsole.layout");
        // attach this to the 'real' root
        base->addChild(sheet);

    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

//    d_console = new Console();

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "GameSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pRSQ = m_pSceneMgr->createRayQuery(Ray());
//    m_pRSQ->setQueryMask(OGRE_HEAD_MASK);

    m_pCamera = m_pSceneMgr->createCamera("GameCamera");
    m_pCamera->setPosition(Vector3(5, 60, 60));
    m_pCamera->lookAt(Vector3(5, 20, 0));
    m_pCamera->setNearClipDistance(5);

    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
    m_pCurrentObject = 0;

//    buildGUI();

    createScene();
}

/*
bool GameState::pause()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pausing GameState...");

    return true;
}
*/

void GameState::resume()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming GameState...");

//    buildGUI();

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
    m_bQuit = false;
}

void GameState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");

    m_pSceneMgr->destroyCamera(m_pCamera);
    m_pSceneMgr->destroyQuery(m_pRSQ);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
}

void GameState::createScene()
{
}

bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef)
{


    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
//        pushAppState(findByName("PauseState"));
        if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
        {
            m_bQuit = true;
            return true;
        }
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


}

bool GameState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}

bool GameState::mouseMoved(const OIS::MouseEvent &evt)
{
	CEGUI::GUIContext& ctx = CEGUI::System::getSingleton().getDefaultGUIContext();

	   ctx.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
	   ctx.injectMouseWheelChange(evt.state.Z.rel / 120.0f);

    return true;
}

bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{

	/*
	if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;

    if(id == OIS::MB_Left)
    {
        onLeftPressed(evt);
        m_bLMouseDown = true;
    }
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = true;
    }
	*/
    CEGUI::System::getSingleton().getDefaultGUIContext().
        injectMouseButtonDown(convertOISButtonToCegui(id));
	
    return true;
}

bool GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().
        injectMouseButtonUp(convertOISButtonToCegui(id));
    return true;
}

void GameState::onLeftPressed(const OIS::MouseEvent &evt)
{
}

void GameState::moveCamera()
{

}

void GameState::getInput()
{

}

void GameState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
//    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

    CEGUI::System& gui_system(CEGUI::System::getSingleton());

    gui_system.injectTimePulse(timeSinceLastFrame);
    gui_system.getDefaultGUIContext().injectTimePulse(timeSinceLastFrame);

    if(m_bQuit == true)
    {
        popAppState();
        return;
    }

//    if(!OgreFramework::getSingletonPtr()->m_pTrayMgr->isDialogVisible())
    {

		/*
		if(m_pDetailsPanel->isVisible())
        {
            m_pDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(m_pCamera->getDerivedPosition().x));
            m_pDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(m_pCamera->getDerivedPosition().y));
            m_pDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(m_pCamera->getDerivedPosition().z));
            m_pDetailsPanel->setParamValue(3, Ogre::StringConverter::toString(m_pCamera->getDerivedOrientation().w));
            m_pDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(m_pCamera->getDerivedOrientation().x));
            m_pDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(m_pCamera->getDerivedOrientation().y));
            m_pDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(m_pCamera->getDerivedOrientation().z));
            if(m_bSettingsMode)
                m_pDetailsPanel->setParamValue(7, "Buffered Input");
            else
                m_pDetailsPanel->setParamValue(7, "Un-Buffered Input");
        }
		*/
    }

    m_MoveScale = m_MoveSpeed   * timeSinceLastFrame;
    m_RotScale  = m_RotateSpeed * timeSinceLastFrame;

    m_TranslateVector = Vector3::ZERO;

    getInput();
    moveCamera();
}


CEGUI::MouseButton GameState::convertOISButtonToCegui(int buttonID)
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


//Console class
// these must match the IDs assigned in the layout
const unsigned int Console::SubmitButtonID = 1;
const unsigned int Console::EntryBoxID     = 2;
const unsigned int Console::HistoryID      = 3;


Console::Console(CEGUI::Window* parent) :
    d_root(CEGUI::WindowManager::getSingleton().loadLayoutFromFile("XsiliumConsole.layout")),
    d_historyPos(0)
{
    using namespace CEGUI;

    // we will destroy the console box windows ourselves
    d_root->setDestroyedByParent(false);

    // Do events wire-up
    d_root->subscribeEvent(Window::EventKeyDown, Event::Subscriber(&Console::handleKeyDown, this));

    d_root->getChild(SubmitButtonID)->
        subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Console::handleSubmit, this));

    d_root->getChild(EntryBoxID)->
        subscribeEvent(Editbox::EventTextAccepted, Event::Subscriber(&Console::handleSubmit, this));

    // decide where to attach the console main window
    parent = parent ? parent : CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

    // attach this window if parent is valid
    if (parent)
        parent->addChild(d_root);
}

Console::~Console()
{
    // destroy the windows that we loaded earlier
    CEGUI::WindowManager::getSingleton().destroyWindow(d_root);
}

void Console::toggleVisibility()
{
    d_root->isVisible() ? d_root->hide() : d_root->show();
}

bool Console::isVisible() const
{
    return d_root->isEffectiveVisible();
}

bool Console::handleSubmit(const CEGUI::EventArgs&)
{
    using namespace CEGUI;

    // get the text entry editbox
    Editbox* editbox = static_cast<Editbox*>(d_root->getChild(EntryBoxID));
    // get text out of the editbox
    CEGUI::String edit_text(editbox->getText());

    // if the string is not empty
    if (!edit_text.empty())
    {
        // add this entry to the command history buffer
        d_history.push_back(edit_text);
        // reset history position
        d_historyPos = d_history.size();
        // append newline to this entry
        edit_text += '\n';
        // get history window
        MultiLineEditbox* history = static_cast<MultiLineEditbox*>(d_root->getChild(HistoryID));
        // append new text to history output
        history->setText(history->getText() + edit_text);
        // scroll to bottom of history output
        history->setCaretIndex(static_cast<size_t>(-1));
        // erase text in text entry box.
        editbox->setText("");
    }

    // re-activate the text entry box
    editbox->activate();

    return true;
}

bool Console::handleKeyDown(const CEGUI::EventArgs& args)
{
    using namespace CEGUI;

    // get the text entry editbox
    Editbox* editbox = static_cast<Editbox*>(d_root->getChild(EntryBoxID));

    switch (static_cast<const KeyEventArgs&>(args).scancode)
    {
    case Key::ArrowUp:
        d_historyPos = ceguimax(d_historyPos - 1, -1);
        if (d_historyPos >= 0)
        {
            editbox->setText(d_history[d_historyPos]);
            editbox->setCaretIndex(static_cast<size_t>(-1));
        }
        else
        {
            editbox->setText("");
        }

        editbox->activate();
        break;

    case Key::ArrowDown:
        d_historyPos = ceguimin(d_historyPos + 1, static_cast<int>(d_history.size()));
        if (d_historyPos < static_cast<int>(d_history.size()))
        {
            editbox->setText(d_history[d_historyPos]);
            editbox->setCaretIndex(static_cast<size_t>(-1));
        }
        else
        {
            editbox->setText("");
        }

        editbox->activate();
        break;

    default:
        return false;
    }

    return true;
}
