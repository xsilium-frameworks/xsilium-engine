#import "XsiliumApp.h"

@implementation XsiliumDelegate

@synthesize window, ogreView;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    xsilium = new XsiliumApp();
    // create a timer that causes OGRE to render at 50fps
    [NSTimer scheduledTimerWithTimeInterval:0.02 target:self selector:@selector(renderFrame)
                                   userInfo:NULL repeats:YES];
    xsilium->startXsilium();
}

- (void) dealloc {
    if(xsilium != NULL) delete xsilium;
    [super dealloc];
}

- (void)renderFrame
{
    Ogre::Root::getSingleton().renderOneFrame(); 
}


@end
