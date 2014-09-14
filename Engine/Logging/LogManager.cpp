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

	LOG(INFO) << "Essais de easylogging";

}
LogManager::~LogManager() {

}

} /* namespace Engine */