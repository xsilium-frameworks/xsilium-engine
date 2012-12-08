/*
 * \file GameStateManager.h
 *
 *  Created on: \date 8 déc. 2012
 *      Author: \author joda
 *  \brief :
 */

#ifndef GAMESTATEMANAGER_H_
#define GAMESTATEMANAGER_H_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>

#include <OgreParticleSystem.h>


#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include "GameState.h"



/*
 *
 */
class GameStateManager {
public:
    /** Holds information about the states in order to
        manage them properly and provide access. */
    typedef struct
    {
        Ogre::String name;
        GameState *state;
    } state_info;

    /** Constructs the GameStateManager.  Must have all
        input, output, gui functions in order to manage
        states. */
    GameStateManager();

    /** Cleans up the states before the instance dies. */
    ~GameStateManager();

    /** Store a game state to manage. */
    void ManageGameState(Ogre::String state_name,GameState *state);

    /** Find a game state by name. */
    GameState *findByName(Ogre::String state_name);

    /** Start game state */
    void start(GameState *state);

    /** Change to a new game state */
    void changeGameState(GameState* state);

    /** Push game state onto the stack. */
    bool pushGameState(GameState* state);

    /** Pop a game state off the stack. */
    void popGameState(void);

    /** This is a special case function to cause a shutdown. */
    void Shutdown(void);

protected:
    /** This initializes a state to receive the events. */
    void init(GameState *state);

    /** This removes event handling from a previous state. */
    void cleanup(GameState *state);

    /** This is the stack where the active states are stored. */
    std::vector<GameState*> mStateStack;
    /** This holds the states that are being managed. */
    std::vector<state_info> mStates;
    /** System Information. */
    device_info *mDevice;
    /** If this is set to true, the game state manager prepares to exit. */
    bool mShutdown;
private:
    InputManager * inputManager;
};

#endif /* GAMESTATEMANAGER_H_ */
