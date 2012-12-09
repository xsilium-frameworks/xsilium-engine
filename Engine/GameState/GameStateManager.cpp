#include "GameStateManager.h"

#include <Ogre.h>

GameStateManager::GameStateManager()
{
	m_bShutdown = false;
    inputManager = InputManager::getSingletonPtr();
}

GameStateManager::~GameStateManager()
{
	state_info si;

    while(!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->exit();
		m_ActiveStateStack.pop_back();
	}

	while(!m_States.empty())
	{
		si = m_States.back();
        si.state->destroy();
        m_States.pop_back();
	}

}

void GameStateManager::manageGameState(Ogre::String stateName, GameState* state)
{
	try
	{
		state_info new_state_info;
		new_state_info.name = stateName;
		new_state_info.state = state;
		m_States.push_back(new_state_info);
	}
	catch(std::exception& e)
	{
		delete state;
		throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "Erreur de gestion d'un nouveau état\n" + Ogre::String(e.what()), "GameStateManager.cpp (39)");
	}
}

GameState* GameStateManager::findByName(Ogre::String stateName)
{
	std::vector<state_info>::iterator itr;

	for(itr=m_States.begin();itr!=m_States.end();itr++)
	{
		if(itr->name==stateName)
			return itr->state;
	}

	return 0;
}

void GameStateManager::start(GameState* state)
{
	changeGameState(state);

	int timeSinceLastFrame = 1;
	int startTime = 0;

	while(!m_bShutdown)
	{
		if(XsiliumFramework::getInstance()->m_pRenderWnd->isClosed())m_bShutdown = true;

		Ogre::WindowEventUtilities::messagePump();

		if(XsiliumFramework::getInstance()->m_pRenderWnd->isActive())
		{
			startTime = XsiliumFramework::getInstance()->m_pTimer->getMillisecondsCPU();

			inputManager->capture();

			m_ActiveStateStack.back()->update(timeSinceLastFrame);

			XsiliumFramework::getInstance()->updateOgre(timeSinceLastFrame);
			XsiliumFramework::getInstance()->m_pRoot->renderOneFrame();

			timeSinceLastFrame = XsiliumFramework::getInstance()->m_pTimer->getMillisecondsCPU() - startTime;
		}
		else
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
		}
	}

	XsiliumFramework::getInstance()->m_pLog->logMessage("Sortie de la boucle principale");
}

void GameStateManager::changeGameState(GameState* state)
{
	if(!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->exit();
		m_ActiveStateStack.pop_back();
	}

	m_ActiveStateStack.push_back(state);
	init(state);
	m_ActiveStateStack.back()->enter();
}

bool GameStateManager::pushGameState(GameState* state)
{
	if(!m_ActiveStateStack.empty())
	{
		if(!m_ActiveStateStack.back()->pause())
			return false;
	}

	m_ActiveStateStack.push_back(state);
	init(state);
	m_ActiveStateStack.back()->enter();

	return true;
}

void GameStateManager::popGameState()
{
	if(!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->exit();
		m_ActiveStateStack.pop_back();
	}

	if(!m_ActiveStateStack.empty())
	{
		init(m_ActiveStateStack.back());
		m_ActiveStateStack.back()->resume();
	}
    else
		shutdown();
}

void GameStateManager::popAllAndPushGameState(GameState* state)
{
    while(!m_ActiveStateStack.empty())
    {
        m_ActiveStateStack.back()->exit();
        m_ActiveStateStack.pop_back();
    }

    pushGameState(state);
}


void GameStateManager::pauseGameState()
{
	if(!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->pause();
	}

	if(m_ActiveStateStack.size() > 2)
	{
		init(m_ActiveStateStack.at(m_ActiveStateStack.size() - 2));
		m_ActiveStateStack.at(m_ActiveStateStack.size() - 2)->resume();
	}
}


void GameStateManager::shutdown()
{
	m_bShutdown = true;
}

void GameStateManager::init(GameState* state)
{
	XsiliumFramework::getInstance()->m_pRenderWnd->resetStatistics();
}
