#ifndef OGRE_XSILIUM_H
#define OGRE_XSILIUM_H

#include "XsiliumFramework.h"
#include "GameState/GameStateManager.h"

#include "Login/LoginState.h"
#include "Game/JeuxState.h"
#include "Compte/Compte.h"

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__
#import <Cocoa/Cocoa.h>
#import <OSX/OgreOSXCocoaView.h>
#endif


class XsiliumApp
{
public:
	XsiliumApp();
	~XsiliumApp();

	void startXsilium();

private:
	GameStateManager*	m_pGameStateManager;
	Compte * compte;
};


#endif

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__


@interface XsiliumDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
	Ogre::SceneNode *objectNode;
	OgreView *ogreView;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet OgreView *ogreView;

@end

static id mAppDelegate;

#endif
