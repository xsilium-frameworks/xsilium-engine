#import "XsiliumApp.h"

// All this does is suppress some messages in the run log.  NSApplication does not
// implement buttonPressed and apps without a NIB have no target for the action.
@implementation NSApplication (_suppressUnimplementedActionWarning)
- (void) buttonPressed:(id)sender
{
    /* Do nothing */
}
@end

#if __LP64__
// DisplayLink callback
#if USE_DISPLAYLINK
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime,
                                      CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
    if(Ogre::Root::getSingletonPtr() && Ogre::Root::getSingleton().isInitialised())
    {
        NSOpenGLContext *ctx = static_cast<Ogre::OSXCocoaWindow *>(xsiliumApp.getWindow() )->nsopenGLContext();
        CGLContextObj cglContext = (CGLContextObj)[ctx CGLContextObj];
        
        // Lock the context before we render into it.
        CGLLockContext(cglContext);
        
        // Calculate the time since we last rendered.
        Ogre::Real deltaTime = 1.0 / (outputTime->rateScalar * (Ogre::Real)outputTime->videoTimeScale / (Ogre::Real)outputTime->videoRefreshPeriod);
        
        // Make the context current and dispatch the render.
        [ctx makeCurrentContext];
        dispatch_async(dispatch_get_main_queue(), ^(void)
                       {
                           Ogre::Root::getSingleton().renderOneFrame(deltaTime);
                       });
        
        CGLUnlockContext(cglContext);
    }
    else if(Ogre::Root::getSingleton().endRenderingQueued())
    {
        [(XsiliumDelegate *)mAppDelegate shutdown];
    }
    return kCVReturnSuccess;
}
#endif
#endif


@implementation XsiliumDelegate

@synthesize mTimer;
@dynamic mLastFrameTime;

- (NSTimeInterval)mLastFrameTime
{
    return mLastFrameTime;
}

- (void)setLastFrameTime:(NSTimeInterval)frameInterval
{
    // Frame interval defines how many display frames must pass between each time the
    // display link fires. The display link will only fire 30 times a second when the
    // frame internal is two on a display that refreshes 60 times a second. The default
    // frame interval setting of one will fire 60 times a second when the display refreshes
    // at 60 times a second. A frame interval setting of less than one results in undefined
    // behavior.
    if (frameInterval >= 1)
    {
        mLastFrameTime = frameInterval;
    }
}

- (void)go {
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    mLastFrameTime = 1;
    mTimer = nil;
    
    try {
        xsiliumApp = new XsiliumApp();
        xsiliumApp->start();
        Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
        
        // Clear event times
        Ogre::Root::getSingleton().clearEventTimes();
    } catch( Ogre::Exception& e ) {
        std::cerr << "An exception has occurred: " <<
        e.getFullDescription().c_str() << std::endl;
    }
#if __LP64__ && USE_DISPLAYLINK
    CVReturn ret = kCVReturnSuccess;
    // Create a display link capable of being used with all active displays
    ret = CVDisplayLinkCreateWithActiveCGDisplays(&mDisplayLink);
    
    // Set the renderer output callback function
    ret = CVDisplayLinkSetOutputCallback(mDisplayLink, &MyDisplayLinkCallback, self);
    
    // Set the display link for the current renderer
    NSOpenGLContext *ctx = static_cast<Ogre::OSXCocoaWindow *>(xsiliumApp.getWindow())->nsopenGLContext();
    NSOpenGLPixelFormat *fmt = static_cast<Ogre::OSXCocoaWindow *>(xsiliumApp.getWindow())->nsopenGLPixelFormat();
    CGLContextObj cglContext = (CGLContextObj)[ctx CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[fmt CGLPixelFormatObj];
    ret = CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(mDisplayLink, cglContext, cglPixelFormat);
    
    // Activate the display link
    ret = CVDisplayLinkStart(mDisplayLink);
#else
    mTimer = [[NSTimer timerWithTimeInterval: 0.001 target:self selector:@selector(renderOneFrame:) userInfo:self repeats:true] retain];
    [[NSRunLoop currentRunLoop] addTimer:mTimer forMode: NSDefaultRunLoopMode];
    [[NSRunLoop currentRunLoop] addTimer:mTimer forMode: NSEventTrackingRunLoopMode]; // Ensure timer fires during resize
#endif
    [pool release];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    mLastFrameTime = 1;
    mTimer = nil;
    
    [self go];
}

- (void)shutdown {
    if(mDisplayLink)
    {
        CVDisplayLinkStop(mDisplayLink);
        CVDisplayLinkRelease(mDisplayLink);
        mDisplayLink = nil;
    }
    
    [NSApp terminate:nil];
}

- (void)renderOneFrame:(id)sender
{
    if(Ogre::Root::getSingletonPtr() && Ogre::Root::getSingleton().isInitialised() && !Ogre::Root::getSingleton().endRenderingQueued())
    {
        Ogre::Root::getSingleton().renderOneFrame();
    }
    else if(Ogre::Root::getSingleton().endRenderingQueued())
    {
        if(mTimer)
        {
            [mTimer invalidate];
            mTimer = nil;
        }
        delete xsiliumApp;
        [NSApp performSelector:@selector(terminate:) withObject:nil afterDelay:0.0];
     
    }
}


@end
