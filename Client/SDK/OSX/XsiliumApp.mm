#import "XsiliumApp.h"

// All this does is suppress some messages in the run log.  NSApplication does not
// implement buttonPressed and apps without a NIB have no target for the action.
@implementation NSApplication (_suppressUnimplementedActionWarning)
- (void) buttonPressed:(id)sender
{
    /* Do nothing */
}
@end

@implementation XsiliumDelegate

@synthesize window, ogreView;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    XsiliumApp * xsilium = new XsiliumApp() ;
    // create a timer that causes OGRE to render at 50fps
    [NSTimer scheduledTimerWithTimeInterval:0.02 target:self selector:@selector(renderFrame)
                                   userInfo:NULL repeats:YES];
    xsilium->startXsilium();
    
    
}

- (void)renderFrame
{
    Ogre::Root::getSingleton().renderOneFrame(); 
}


@end
