#ifndef OGRE_XSILIUM_H
#define OGRE_XSILIUM_H

#include "Engine/Engine.h"
#include "Game/PlayState.h"
#include "GameState/GameStateManager.h"
#include "Logging/LogManager.h"
#include "Login/LoginState.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE

#define USE_DISPLAYLINK 0
//#import <OSX/OgreOSXCocoaWindow.h>
#import <QuartzCore/CVDisplayLink.h>
#endif

class XsiliumApp
{
public:
	XsiliumApp();
	~XsiliumApp();

	void start();
    
    Ogre::RenderWindow* getWindow();

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
    
    NSDate *mDate;
    NSTimeInterval mLastFrameTime;
    CVDisplayLinkRef mDisplayLink; //display link for managing rendering thread
}

- (void)go;
- (void)renderOneFrame:(id)sender;
- (void)shutdown;

@property (retain, atomic) NSTimer *mTimer;
@property (nonatomic) NSTimeInterval mLastFrameTime;

@end

static XsiliumApp * xsiliumApp;

#if __LP64__
static id mAppDelegate;
#endif

#endif
