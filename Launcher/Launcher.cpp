/*
 * \file Launcher.cpp
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Launcher.h"

Launcher::Launcher() {
	m_pGameStateManager = new GameStateManager();

}

Launcher::~Launcher() {
	delete m_pGameStateManager;
    //XsiliumFramework::DestroyInstance();
}



void Launcher::go()
{
Patcher * patcher = new Patcher();
patcher->start();
Downloader::getInstance();
	//if(!XsiliumFramework::getInstance()->initOgre("Xsilium Launcher"))
	//		return;


}



