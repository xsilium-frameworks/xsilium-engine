#include "XsiliumApp.h"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE && __LP64__
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

	mAppDelegate = [[XsiliumDelegate alloc] init];
	[[NSApplication sharedApplication] setDelegate:mAppDelegate];
	int retVal = NSApplicationMain(argc, (const char **) argv);
 
	[pool release];

	return retVal;
#else

	XsiliumApp xsilium;
	try
	{
		xsilium.startXsilium();
	}
	catch(std::exception& e)
	{
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBoxA(NULL, e.what(), "Une erreur est apparue!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		fprintf(stderr, "Une erreur est apparue: %s\n", e.what());
#endif
	}

	return 0;
#endif
    
}
