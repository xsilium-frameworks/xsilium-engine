/*
 * \file define.h
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef DEFINE_H_
#define DEFINE_H_

/* Application specific definitions */
#define APP_VERSION "VERSION 0.0.1" // used in log
#define APP_NAME "Launcher" // used in Renderer windows titlebar
#define RESOURCE "Launcher.dat"
#define MIRRORS_RESOURCE "patch_mirrors.txt"


#ifdef __linux__
#define PROJECT_LOG_DIR "log"
#define PROJECT_RESOURCES "resources"
#define PROJECT_OGRE_RESOURCES "ogre"
#define PROJECT_TEMP_DIR "tmp"
#define EXTERNAL_APP_PATH "Karazeh"
#define EXTERNAL_APP_NAME "Karazeh"
#define EXTERNAL_APP_ARG "Qt"
const int DISTANCE_FROM_ROOT = 1;
#elif __APPLE__
#define PROJECT_LOG_DIR "Log"
#define PROJECT_RESOURCES "Resources"
#define PROJECT_TEMP_DIR "Temp"
#define EXTERNAL_APP_PATH "Karazeh"
#define EXTERNAL_APP_NAME "Karazeh"
#define EXTERNAL_APP_ARG ""
const int DISTANCE_FROM_ROOT = 1;
#else
#define PROJECT_LOG_DIR "log"
#define PROJECT_RESOURCES "resources"
#define PROJECT_OGRE_RESOURCES "ogre"
#define PROJECT_TEMP_DIR "tmp"
#define EXTERNAL_APP_PATH "Karazeh.exe" // path to the application launched relative to this application
#define EXTERNAL_APP_NAME "Karazeh" // name of the application to be launched
#define EXTERNAL_APP_ARG "" // if you need to pass more than 1 argument, see Launcher::launchExternalApplication()
const int DISTANCE_FROM_ROOT = 2; // how many directories the Launcher is located from the app root
#endif




#endif /* DEFINE_H_ */
