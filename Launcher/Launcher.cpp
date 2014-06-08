/*
 * \file Launcher.cpp
 *
 *  Created on: \date 8 juin 2014
 *      Author: \author joda
 *  \brief :
 */
#include "Launcher.h"

namespace Launcher {

Launcher::Launcher() {
	// TODO Auto-generated constructor stub

}

Launcher::~Launcher() {
	XsiliumFramework::DestroyInstance();
}


void Launcher::start()
{
	if(!XsiliumFramework::getInstance()->initOgre("Xsilium Client","client"))
		return;

	XsiliumFramework::getInstance()->createWindow();

	XsiliumFramework::getInstance()->initInput();

	XsiliumFramework::getInstance()->loadRessource();

	GestionnaireInterface::getInstance()->interfacePrincipal();

}

} /* namespace Launcher */
