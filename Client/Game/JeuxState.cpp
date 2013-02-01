#include "JeuxState.h"
#include "PagedGeometry.h"
#include "GrassLoader.h"
#include "BatchPage.h"
#include "ImpostorPage.h"
#include "TreeLoader3D.h"

using namespace Ogre;

using namespace Forests;

JeuxState::JeuxState()
    :   mTerrainGlobals(0),
      mTerrainGroup(0),
      mTerrainsImported(false)
{
    m_MoveSpeed			= 1.0f;
    m_RotateSpeed		= 0.3f;

    m_bQuit             = false;
    m_bLMouseDown = false;
    m_bRMouseDown = false;

    inputManager = InputManager::getSingletonPtr();
}


void JeuxState::enter()
{
    inputManager->addKeyListener(this,"Game1");
    inputManager->addMouseListener(this,"Game2");


    XsiliumFramework::getInstance()->m_pLog->logMessage("Entering JeuxState...");

    m_pSceneMgr = XsiliumFramework::getInstance()->m_pRoot->createSceneManager(ST_GENERIC, "GameSceneMgr");
    m_pSceneMgr->createLight("Light")->setPosition(75,75,75);

    m_pRSQ = m_pSceneMgr->createRayQuery(Ray());
    m_pRSQ->setQueryMask(OGRE_HEAD_MASK);



    m_pCamera = m_pSceneMgr->createCamera("GameCamera");
    m_pCamera->setPosition(Ogre::Vector3(1683, 50, 2116));
    m_pCamera->lookAt(Ogre::Vector3(1963, 50, 1660));
    m_pCamera->setNearClipDistance(0.1);

    m_pCamera->setAspectRatio(Real(XsiliumFramework::getInstance()->m_pViewport->getActualWidth()) / Real(XsiliumFramework::getInstance()->m_pViewport->getActualHeight()));

    XsiliumFramework::getInstance()->m_pViewport->setCamera(m_pCamera);
    m_pCurrentObject = 0;

    buildGUI();

    createScene();
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

    m_pSceneMgr->destroyCamera(m_pCamera);
    m_pSceneMgr->destroyQuery(m_pRSQ);
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
    DotSceneLoader* pDotSceneLoader = new DotSceneLoader();
    pDotSceneLoader->parseDotScene("CubeScene.xml", "General", m_pSceneMgr, m_pSceneMgr->getRootSceneNode());
    delete pDotSceneLoader;

    Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
      lightdir.normalise();

      Ogre::Light* light = m_pSceneMgr->createLight("tstLight");
      light->setType(Ogre::Light::LT_DIRECTIONAL);
      light->setDirection(lightdir);
      light->setDiffuseColour(Ogre::ColourValue::White);
      light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

      m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

//    m_pSceneMgr->getEntity("Cube01")->setQueryFlags(CUBE_MASK);
//    m_pSceneMgr->getEntity("Cube02")->setQueryFlags(CUBE_MASK);
//    m_pSceneMgr->getEntity("Cube03")->setQueryFlags(CUBE_MASK);

//    m_pOgreHeadEntity = m_pSceneMgr->createEntity("OgreHeadEntity", "ogrehead.mesh");
//    m_pOgreHeadEntity->setQueryFlags(OGRE_HEAD_MASK);
//    m_pOgreHeadNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("OgreHeadNode");
//    m_pOgreHeadNode->attachObject(m_pOgreHeadEntity);
//    m_pOgreHeadNode->setPosition(Vector3(0, 0, -25));

//    m_pOgreHeadMat = m_pOgreHeadEntity->getSubEntity(1)->getMaterial();
//    m_pOgreHeadMatHigh = m_pOgreHeadMat->clone("OgreHeadMatHigh");
//    m_pOgreHeadMatHigh->getTechnique(0)->getPass(0)->setAmbient(1, 0, 0);
//    m_pOgreHeadMatHigh->getTechnique(0)->getPass(0)->setDiffuse(1, 0, 0, 0);

    mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

        mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(m_pSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
        mTerrainGroup->setFilenameConvention(Ogre::String("base-terrain"), Ogre::String("dat"));
        mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

        configureTerrainDefaults(light);

        for (long x = 0; x <= 0; ++x)
            for (long y = 0; y <= 0; ++y)
                defineTerrain(x, y);

        // sync load since we want everything in place when we start
        mTerrainGroup->loadAllTerrains(true);

        if (mTerrainsImported)
        {
            Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
            while(ti.hasMoreElements())
            {
                Ogre::Terrain* t = ti.getNext()->instance;
                initBlendMaps(t);
            }
        }

        mTerrainGroup->freeTemporaryResources();
}

void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
    img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    if (flipX)
        img.flipAroundY();
    if (flipY)
        img.flipAroundX();
}

void JeuxState::defineTerrain(long x, long y)
{
    Ogre::String filename = mTerrainGroup->generateFilename(x, y);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
    {
        mTerrainGroup->defineTerrain(x, y);
    }
    else
    {
        Ogre::Image img;
        getTerrainImage(x % 2 != 0, y % 2 != 0, img);
        mTerrainGroup->defineTerrain(x, y, &img);
        mTerrainsImported = true;
    }
}

void JeuxState::initBlendMaps(Ogre::Terrain* terrain)
{
    Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
    Ogre::Real minHeight0 = 70;
    Ogre::Real fadeDist0 = 40;
    Ogre::Real minHeight1 = 70;
    Ogre::Real fadeDist1 = 15;
    float* pBlend1 = blendMap1->getBlendPointer();
    for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real tx, ty;

            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);

            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = val;
        }
    }
    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
}

void JeuxState::configureTerrainDefaults(Ogre::Light* light)
{
    // Configure global
    mTerrainGlobals->setMaxPixelError(8);
    // testing composite map
    mTerrainGlobals->setCompositeMapDistance(3000);

    // Important to set these so that the terrain knows what to use for derived (non-realtime) data
    mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
    mTerrainGlobals->setCompositeMapAmbient(m_pSceneMgr->getAmbientLight());
    mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

    // Configure default import settings for if we use imported image
    Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 513;
    defaultimp.worldSize = 12000.0f;
    defaultimp.inputScale = 600;
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;
    // textures
    defaultimp.layerList.resize(3);
    defaultimp.layerList[0].worldSize = 100;
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
    defaultimp.layerList[1].worldSize = 30;
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
    defaultimp.layerList[2].worldSize = 200;
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
}

void JeuxState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;

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


