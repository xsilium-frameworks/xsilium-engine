#include "GameStateManager.h"

namespace Engine {

GameStateManager::GameStateManager() {
	inputManager = InputManager::getInstance();
	Engine::getInstance()->addListenner(this);
	Engine::getInstance()->getRoot()->addFrameListener(this);
}

GameStateManager::~GameStateManager() {
	Engine::getInstance()->getRoot()->removeFrameListener(this);
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

void GameStateManager::addGameState(Ogre::String stateName, GameState* state) {
	try {
		state_info new_state_info;
		new_state_info.name = stateName;
		new_state_info.state = state;
		m_States.push_back(new_state_info);
	} catch (std::exception& e) {
		delete state;
		throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR,
				"Erreur de gestion d'un nouveau �tat\n"
						+ Ogre::String(e.what()), "GameStateManager.cpp (39)");
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

	if (Engine::getInstance()->getRoot()->getRenderSystem() != NULL) {
		Engine::getInstance()->getRoot()->startRendering(); // start the render loop
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

bool GameStateManager::frameRenderingQueued(
		const Ogre::FrameEvent& m_FrameEvent) {
	if (!m_ActiveStateStack.empty()) {
		if (!isEmpty()) {
			Event* event = getEvent();
			processEvent(event);
			deleteEvent();
		}
		m_ActiveStateStack.back()->update(m_FrameEvent.timeSinceLastFrame);
	}

	return true;
}

void GameStateManager::processEvent(Event * event) {
	if (event->hasProperty("GAME")) {
		if (event->hasProperty("ChangeGameState"))
		{
			GameState * gameStateTemp = findByName(event->getProperty("ChangeGameState").c_str());
			if (gameStateTemp != NULL)
				changeGameState(gameStateTemp);
		}
	}

	m_ActiveStateStack.back()->processEvent(event);
}

void GameStateManager::shutdown() {
	//Engine::getInstance()->getLog()->logMessage("Sortie de la boucle principale");
	Engine::getInstance()->stopEngine();
}

void GameStateManager::init(GameState* state) {
	//Engine::getInstance()->getRenderWindow()->resetStatistics();
}

}
