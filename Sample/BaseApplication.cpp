#include "BaseApplication.h"
 

BaseApplication::BaseApplication(void)
    : mRenderer(0)
{
}

BaseApplication::~BaseApplication(void)
{
}
 

void BaseApplication::createScene(void)
{
    using namespace CEGUI;

    //mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();



    ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    Font::setDefaultResourceGroup("Fonts");
    Scheme::setDefaultResourceGroup("Schemes");
    WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    //WindowManager::getSingleton().setDefaultResourceGroup("Layouts");
 
    //SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
 
    //CEGUI::System::getSingleton().setDefaultMouseCursor("Vanilla-Images", "MouseArrow");
 
    /*WindowManager &wmgr = WindowManager::getSingleton();
    CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIApp/Sheet");

 
    sheet->addChild(wmgr.loadLayoutFromFile("authentification.layout"));


	CEGUI::Window *title = sheet->getChild("CEGUIApp/title");
	title->setText("Identification");

	CEGUI::Window *submit = sheet->getChild("CEGUIApp/submit");
	submit->setText("Connexion");
	
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);*/

 
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    mSceneMgr->setSkyDome(true, "Xsilium/CloudySky", 5, 8);

	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);
}
 
void BaseApplication::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
 
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
 
    mInputManager = OIS::InputManager::createInputSystem( pl );
 
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
 
    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);
 
    //Set initial mouse clipping size
    windowResized(mWindow);
 
    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
 
    mRoot->addFrameListener(this);
}
 
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;
 
    if(mShutDown)
        return false;
 
    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
 
    return true;
}
 
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
    //CEGUI::System &sys = CEGUI::System::getSingleton();
    //sys.injectKeyDown(arg.key);
    //sys.injectChar(arg.text);
 
    if (arg.key == OIS::KC_ESCAPE)
    {
		//CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
		//CEGUI::Window *esc = wmgr.getWindow("CEGUIEsc/");
		//CEGUI::Window *btnYes = wmgr.getWindow("CEGUIEsc/butnOui");
		//CEGUI::Window *btnNo = wmgr.getWindow("CEGUIEsc/butnNon");
		//esc->show();
		//btnYes->subscribeEvent(CEGUI::PushButton::EventClicked,
        //CEGUI::Event::Subscriber(&BaseApplication::quit, this));
	}

	if (arg.key == OIS::KC_H && mHide == false)
	{
		//CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
		//CEGUI::Window *sheet = wmgr.getWindow("CEGUIApp/Sheet");
		//sheet->hide();
		mHide = true;
	}

	else if  (arg.key == OIS::KC_H && mHide == true)

	{
	//CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
		//CEGUI::Window *sheet = wmgr.getWindow("CEGUIApp/Sheet");
		//sheet->show();
		mHide = false;


	}
 
    mCameraMan->injectKeyDown(arg);
    return true;
}
 
bool BaseApplication::keyReleased( const OIS::KeyEvent &arg )
{
    //if(CEGUI::System::getSingleton().injectKeyUp(arg.key)) return true;
    mCameraMan->injectKeyUp(arg);
    return true;
}
 
CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
        break;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
        break;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
        break;
 
    default:
        return CEGUI::LeftButton;
        break;
    }
}
 
bool BaseApplication::mouseMoved( const OIS::MouseEvent &arg )
{
    //if(CEGUI::System::getSingleton().injectMouseMove(arg.state.X.rel, arg.state.Y.rel)) return true;
    mCameraMan->injectMouseMove(arg);
    return true;
}
 
bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //if(CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id))) return true;
    mCameraMan->injectMouseDown(arg, id);
    return true;
}
 
bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //if(CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id))) return true;
    mCameraMan->injectMouseUp(arg, id);
    return true;
}
 
bool BaseApplication::quit(const CEGUI::EventArgs &e)
{
    mShutDown = true;
    return true;
}
 
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        BaseApplication app;
 
        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif

