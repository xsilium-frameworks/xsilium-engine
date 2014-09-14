/*
 * \file LogManager.cpp
 *
 *  Created on: \date 12 septembre 2014
 *      Author: \author xelfe
 *  \brief : Fichier source de la classe LogManager
 */
#define _ELPP_STL_LOGGING
#define _ELPP_THREAD_SAFE

#include "LogManager.h"

_INITIALIZE_EASYLOGGINGPP
namespace Engine {

LogManager::LogManager() {

	el::Configurations default;
	default.set(el::Level::Info, el::ConfigurationType::Format, "%datetime %level %msg");
	default.set(el::Level::Info, el::ConfigurationType::Filename, "logs/client.log");
	el::Loggers::reconfigureLogger("default", default);

	LOG(INFO) << "--------- Initialisation du gestionnaire de log ---------";

	default.setGlobally(el::ConfigurationType::Format, "%date %msg");

	el::Loggers::reconfigureLogger("default", default);

}
LogManager::~LogManager() {

}

} /* namespace Engine */