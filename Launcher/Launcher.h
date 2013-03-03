/*
 * \file Launcher.h
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef LAUNCHER_H_
#define LAUNCHER_H_

#include "GameState/GameStateManager.h"
#include "Downloader/Downloader.h"
#include "Patcher/Patcher.h"

/*
 *
 */
class Launcher {
public:
	Launcher();
	virtual ~Launcher();

	void go();

	/*! \brief
	 * Destroys all components, namely the Patcher, Downloader, and the Renderer
	 * effectively cleaning up.
	 *
	 * \warn
	 * This will call the Renderer's destructor so make sure you're not calling it
	 * directly from there. This method should be avoided unless the Renderer is
	 * a wrapper as is the case with Cocoa's.
	 */
	void shutdown();

	/*! \brief
	 *  Terminates the current process and launches the application found at
	 *  inPath identified by inAppName using execl();
	 *
	 *  \arg inPath: full path to the application with extension, ie C:\\Foo.exe
	 *  \arg inAppName: stripped name of the application, ie Foo
	 */
	void launchExternalApp();

	bool isLaunching() { return fLaunching; };

	/*! \brief
	 *	Shuts down the system and all components.
	 */
	void requestShutdown();

	/*! \brief
	 *  Calls the Patcher to validate the client.
	 *
	 * \warn
	 * This MUST be called before initPatching()
	 */
	void startValidation();

	/*! \brief
	 *  Calls the Patcher to update the client.
	 *
	 * \warn
	 * Make sure you call this after the validation is complete. Renderers
	 * are injected upon validation completion.
	 */
	void startPatching();


private:
	GameStateManager*	m_pGameStateManager;

    bool fLaunching;
    bool fShutdown;
};

#endif /* LAUNCHER_H_ */
