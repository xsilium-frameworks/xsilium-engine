#ifndef OGRE_XSILIUM_H
#define OGRE_XSILIUM_H

#include "XsiliumFramework.h"
#include "GameState/GameStateManager.h"

#include "Login/LoginState.h"
#include "Game/JeuxState.h"
#include "Compte/Compte.h"

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE)
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

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE)

#if defined(MAC_OS_X_VERSION_10_6) && MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
@interface XsiliumDelegate : NSObject <NSApplicationDelegate>
#else
@interface XsiliumDelegate : NSObject
#endif
{
    NSTimer *mTimer;
    NSTimeInterval mLastFrameTime;
    XsiliumApp *xsilium;
}

- (void)renderOneFrame:(id)sender;

@property (retain) NSTimer *mTimer;
@property (nonatomic) NSTimeInterval mLastFrameTime;

@end

#if __LP64__
static id mAppDelegate;
#endif

#endif
