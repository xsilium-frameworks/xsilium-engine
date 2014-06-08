/*
 * \file Launcher.h
 *
 *  Created on: \date 8 juin 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef LAUNCHER_H_
#define LAUNCHER_H_

#include "XsiliumFramework.h"
#include "Interface/GestionnaireInterface.h"

namespace Launcher {

/*
 *
 */
class Launcher {
public:
	Launcher();
	virtual ~Launcher();

	void start();
};

} /* namespace Launcher */

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE)

#if defined(MAC_OS_X_VERSION_10_6) && MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
@interface LauncherDelegate : NSObject <NSApplicationDelegate>
#else
@interface LauncherDelegate : NSObject
#endif
{
    NSTimer *mTimer;
    NSTimeInterval mLastFrameTime;
	Launcher::Launcher * launcher;
}

- (void)renderOneFrame:(id)sender;

@property (retain) NSTimer *mTimer;
@property (nonatomic) NSTimeInterval mLastFrameTime;

@end

#if __LP64__
static id mAppDelegate;
#endif

#endif

#endif /* LAUNCHER_H_ */
