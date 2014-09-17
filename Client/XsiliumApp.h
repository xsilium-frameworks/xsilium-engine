#ifndef OGRE_XSILIUM_H
#define OGRE_XSILIUM_H

#include "Engine/Engine.h"
#include "Graphics/GraphicsManager.h"
#include "GameState/GameStateManager.h"
#include "Gui/GuiManager.h"
#include "Logging/LogManager.h"
#include "Login/LoginState.h"
#include "Input/KeyboardManager.h"

class XsiliumApp
{
public:
	XsiliumApp();
	~XsiliumApp();

	void start();

private:
	Engine::GraphicsManager* graphicsManager;
	Engine::GameStateManager* gameStateManager;
	Engine::GuiManager* guiManager;
	Engine::LogManager* logManager;

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
