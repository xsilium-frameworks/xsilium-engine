#include "Launcher.h"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
	Launcher launcher;
	try
	{
		launcher.go();
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
}
