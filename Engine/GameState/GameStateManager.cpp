#include "GameStateManager.h"

namespace Engine {

GameStateManager::GameStateManager() {
    inputManager = InputManager::getInstance();
    m_pRoot = 0;
    m_pRenderWnd = 0;
    EventManager::getInstance()->addListenneur(this);
}

GameStateManager::~GameStateManager() {
    m_pRoot->removeFrameListener(this);
    state_info si;

    while (!m_ActiveStateStack.empty()) {
        m_ActiveStateStack.back()->exit();
        m_ActiveStateStack.pop_back();
    }

    while (!m_States.empty()) {
        si = m_States.back();
        si.state->destroy();
        m_States.pop_back();
    }

}

void GameStateManager::setRoot(Ogre::Root* m_pRoot) {
    this->m_pRoot = m_pRoot;
    m_pRoot->addFrameListener(this);
}

void GameStateManager::setRenderWindow(Ogre::RenderWindow* m_pRenderWnd) {
    this->m_pRenderWnd = m_pRenderWnd;
}

void GameStateManager::addGameState(Ogre::String stateName, GameState* state) {
    try {
        state_info new_state_info;
        new_state_info.name = stateName;
        new_state_info.state = state;
        m_States.push_back(new_state_info);
    } catch (std::exception& e) {
        delete state;
        throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR,
                "Erreur de gestion d'un nouveau �tat\n" + Ogre::String(e.what()),
                "GameStateManager.cpp (39)");
    }
}

GameState* GameStateManager::findByName(Ogre::String stateName) {
    std::vector<state_info>::iterator itr;

    for (itr = m_States.begin(); itr != m_States.end(); itr++) {
        if (itr->name == stateName)
            return itr->state;
    }

    return NULL;
}

void GameStateManager::start(GameState* state) {
    changeGameState(state);
#if  (!__LP64__ || OGRE_PLATFORM != OGRE_PLATFORM_APPLE)

    if (m_pRoot->getRenderSystem() != NULL) {
        m_pRoot->startRendering(); // start the render loop
    }

#endif

}

void GameStateManager::changeGameState(GameState* state) {

    if (!m_ActiveStateStack.empty()) {
        m_ActiveStateStack.back()->exit();
        m_ActiveStateStack.pop_back();
    }

    m_ActiveStateStack.push_back(state);
    init(state);
    m_ActiveStateStack.back()->enter();
}

bool GameStateManager::pushGameState(GameState* state) {
    if (!m_ActiveStateStack.empty()) {
        if (!m_ActiveStateStack.back()->pause())
            return false;
    }

    m_ActiveStateStack.push_back(state);
    init(state);
    m_ActiveStateStack.back()->enter();

    return true;
}

void GameStateManager::popGameState() {
    if (!m_ActiveStateStack.empty()) {
        m_ActiveStateStack.back()->exit();
        m_ActiveStateStack.pop_back();
    }

    if (!m_ActiveStateStack.empty()) {
        init(m_ActiveStateStack.back());
        m_ActiveStateStack.back()->resume();
    } else
        shutdown();
}

void GameStateManager::popAllAndPushGameState(GameState* state) {
    while (!m_ActiveStateStack.empty()) {
        m_ActiveStateStack.back()->exit();
        m_ActiveStateStack.pop_back();
    }

    pushGameState(state);
}

bool GameStateManager::frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent) {
    if (!m_ActiveStateStack.empty()) {
        m_ActiveStateStack.back()->update(m_FrameEvent.timeSinceLastFrame);
    }

    return true;
}

void GameStateManager::processEvent(Event * event) {
    if (event->hasProperty("GAME")) {
        if (event->hasProperty("ChangeGameState")) {
            GameState * gameStateTemp = findByName(event->getProperty("ChangeGameState").c_str());
            if (gameStateTemp != NULL)
                changeGameState(gameStateTemp);
        }
    }

    if( !m_ActiveStateStack.empty() )
        m_ActiveStateStack.back()->processEvent(event);
}

void GameStateManager::shutdown() {
    LogManager::getInstance()->setLogMessage("Sortie de la boucle principale", NORMAL);
    Event event;
    event.setProperty("ENGINE", "1");
    event.setProperty("Fonction", "QUIT");
    Engine::EventManager::getInstance()->addEvent(event);
}

void GameStateManager::init(GameState* state) {
    m_pRenderWnd->resetStatistics();
}

}
