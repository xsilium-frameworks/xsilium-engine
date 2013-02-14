#include "JeuxState.h"
#include "PagedGeometry.h"
#include "GrassLoader.h"
#include "BatchPage.h"
#include "ImpostorPage.h"
#include "TreeLoader3D.h"

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

    mSkyX = 0;
    mBasicController = 0;
    mHydrax = 0;
}


void JeuxState::enter()
{
    inputManager->addKeyListener(this,"Game1");
    inputManager->addMouseListener(this,"Game2");


    XsiliumFramework::getInstance()->m_pLog->logMessage("Entering JeuxState...");

    createScene();

    buildGUI();
}


bool JeuxState::pause()
{
    XsiliumFramework::getInstance()->m_pLog->logMessage("Pausing JeuxState...");

    return true;
}


void JeuxState::resume()
{
    XsiliumFramework::getInstance()->m_pLog->logMessage("Resuming JeuxState...");

    XsiliumFramework::getInstance()->m_pViewport->setCamera(m_pCamera);
    m_bQuit = false;
}

void JeuxState::exit()
{
    XsiliumFramework::getInstance()->m_pLog->logMessage("Leaving JeuxState...");

    XsiliumFramework::getInstance()->m_pRoot->removeFrameListener(mSkyX);
    XsiliumFramework::getInstance()->m_pRenderWnd->removeListener(mSkyX);

    delete mHydrax;

    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        XsiliumFramework::getInstance()->m_pRoot->destroySceneManager(m_pSceneMgr);

    CEGUI::WindowManager::getSingleton().destroyAllWindows();


    inputManager->removeKeyListener(this);
    inputManager->removeMouseListener(this);
}

void JeuxState::buildGUI()
{

	using namespace CEGUI;
    CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());

    CEGUI::Window* parent = winMgr.createWindow("DefaultWindow", "CEGUIApp/Console");

    CEGUI::Window* d_root = winMgr.loadLayoutFromFile("XsiliumConsole.layout");

    Console * d_console = new Console(d_root);

    // we will destroy the console box windows ourselves
    d_root->setDestroyedByParent(false);

        // Do events wire-up
    d_root->subscribeEvent(CEGUI::Window::EventKeyDown, Event::Subscriber(&Console::handleKeyDown, d_console));

    d_root->getChild("Console/Button")->
            subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Console::handleSubmit, d_console));

    d_root->getChild("Console/Editbox")->
            subscribeEvent(Editbox::EventTextAccepted, Event::Subscriber(&Console::handleSubmit, d_console));

        // attach this window if parent is valid
    parent->addChild(d_root);

    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(d_root);
}

void JeuxState::createScene()
{
	m_pSceneMgr = XsiliumFramework::getInstance()->m_pRoot->createSceneManager(ST_GENERIC, "GameSceneMgr");

    m_Loader = new DotSceneLoader();
    m_Loader->parseDotScene("test-terrain.scene", "General", m_pSceneMgr);

    // Loop through all cameras and grab their name and set their debug representation
     Ogre::SceneManager::CameraIterator cameras = m_pSceneMgr->getCameraIterator();
     while (cameras.hasMoreElements())
     {
         Ogre::Camera* camera = cameras.getNext();
         mCamNames.push_back(camera->getName());
         Ogre::Entity* debugEnt = m_pSceneMgr->createEntity(camera->getName() + Ogre::String("_debug"), "scbCamera.mesh");

             Ogre::SceneNode* pNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(camera->getName());
             pNode->setPosition(camera->getPosition());
             pNode->setOrientation(camera->getOrientation());

             pNode->attachObject(debugEnt);
             pNode->scale(0.5, 0.5, 0.5);
     }

     // Grab the first available camera, for now
     Ogre::String cameraName = mCamNames[0];
     try
     {
         m_pCamera = m_pSceneMgr->getCamera(cameraName);
         XsiliumFramework::getInstance()->m_pRenderWnd->getViewport(0)->setCamera(m_pCamera);
        // mCameraMan->setCamera(m_pCamera);
         m_pSceneMgr->getEntity(m_pCamera->getName() + Ogre::String("_debug"))->setVisible(false);

         for(unsigned int ij = 0;ij < m_Loader->mPGHandles.size();ij++)
         {
             m_Loader->mPGHandles[ij]->setCamera(m_pCamera);
         }

     }
     catch (Ogre::Exception& e)
     {
         Ogre::LogManager::getSingleton().logMessage("SampleApp::createScene : setting the active camera to (\"" +
             cameraName + ") failed: " + e.getFullDescription());
     }

		mBasicController = new SkyX::BasicController();
		mSkyX = new SkyX::SkyX(m_pSceneMgr, mBasicController);
		mSkyX->create();

		mBasicController->setMoonPhase(0.0f);
		mSkyX->setTimeMultiplier(0.2f);

		XsiliumFramework::getInstance()->m_pRoot->addFrameListener(mSkyX);
		XsiliumFramework::getInstance()->m_pRenderWnd->addListener(mSkyX);


		mSkyX->getCloudsManager()->add(SkyX::CloudLayer::Options(/* Default options */));



		mHydrax = new Hydrax::Hydrax(m_pSceneMgr, m_pCamera, XsiliumFramework::getInstance()->m_pRenderWnd->getViewport(0));


		Hydrax::Module::ProjectedGrid *mModule
					= new Hydrax::Module::ProjectedGrid(mHydrax,new Hydrax::Noise::Perlin(/*Generic one*/),
					                                    Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
														// Normal mode
														Hydrax::MaterialManager::NM_VERTEX,
														// Projected grid options
												        Hydrax::Module::ProjectedGrid::Options());

				// Set our module
				mHydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));

				// Load all parameters from config file
				// Remarks: The config file must be in Hydrax resource group.
				// All parameters can be set/updated directly by code(Like previous versions),
				// but due to the high number of customizable parameters, since 0.4 version, Hydrax allows save/load config files.
				mHydrax->loadCfg("HydraxDemo.hdx");


				if (XsiliumFramework::getInstance()->m_pRoot->getRenderSystem()->getName() == "OpenGL Rendering Subsystem")
					mHydrax->setShaderMode( Hydrax::MaterialManager::SM_GLSL);
				else
					mHydrax->setShaderMode( Hydrax::MaterialManager::SM_HLSL);



		        // Create water
		        mHydrax->create();
}

bool JeuxState::frameStarted(const FrameEvent &evt)
{
	mHydrax->update(evt.timeSinceLastFrame);
	return true;
}

void JeuxState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;



   // mHydrax->update(m_FrameEvent.timeSinceLastFrame / 1000);

    CEGUI::System& gui_system(CEGUI::System::getSingleton());

    gui_system.injectTimePulse(timeSinceLastFrame);
    gui_system.getDefaultGUIContext().injectTimePulse(timeSinceLastFrame);

    if(m_bQuit == true)
    {
        popGameState();
        return;
    }
    m_MoveScale = m_MoveSpeed   * timeSinceLastFrame;
    m_RotScale  = m_RotateSpeed * timeSinceLastFrame;

	m_TranslateVector = Ogre::Vector3::ZERO;

    getInput();
    m_pCamera->moveRelative(m_TranslateVector / 10);

}

void JeuxState::getInput()
{
        if(inputManager->getKeyboard()->isKeyDown(OIS::KC_A))
            m_TranslateVector.x = -m_MoveScale;

        if(inputManager->getKeyboard()->isKeyDown(OIS::KC_D))
            m_TranslateVector.x = m_MoveScale;

        if(inputManager->getKeyboard()->isKeyDown(OIS::KC_W))
            m_TranslateVector.z = -m_MoveScale;

        if(inputManager->getKeyboard()->isKeyDown(OIS::KC_S))
            m_TranslateVector.z = m_MoveScale;
        if(inputManager->getKeyboard()->isKeyDown(OIS::KC_0))
        {
        	m_pCamera = m_pSceneMgr->getCamera("Camera#0");
        	XsiliumFramework::getInstance()->m_pRenderWnd->getViewport(0)->setCamera(m_pCamera);
        }
        if(inputManager->getKeyboard()->isKeyDown(OIS::KC_1))
        {
        	m_pCamera = m_pSceneMgr->getCamera("Camera#1");
        	XsiliumFramework::getInstance()->m_pRenderWnd->getViewport(0)->setCamera(m_pCamera);
        }
        if(inputManager->getKeyboard()->isKeyDown(OIS::KC_2))
        {
        	m_pCamera = m_pSceneMgr->getCamera("Camera#2");
        	XsiliumFramework::getInstance()->m_pRenderWnd->getViewport(0)->setCamera(m_pCamera);
        }
}

bool JeuxState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	switch(keyEventRef.key)
	{
	case OIS::KC_ESCAPE:
		m_bQuit = true;
		break;
	case OIS::KC_LSHIFT:
			m_pCamera->moveRelative(m_TranslateVector);
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

bool JeuxState::mouseMoved( const OIS::MouseEvent &event )
{
	if(m_bLMouseDown)
	{
		m_pCamera->yaw(Degree(event.state.X.rel * -0.1f));
	    m_pCamera->pitch(Degree(event.state.Y.rel * -0.1f));
	}
	return true;
}
bool JeuxState::mousePressed( const OIS::MouseEvent &event, OIS::MouseButtonID id )
{
    if(id == OIS::MB_Left)
    {
        m_bLMouseDown = true;
    }
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = true;
    }

	return true;
}
bool JeuxState::mouseReleased( const OIS::MouseEvent &event, OIS::MouseButtonID id )
{
    if(id == OIS::MB_Left)
    {
        m_bLMouseDown = false;
    }
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = false;
    }
	return true;
}


