/*
 * \file LogManager.cpp
 *
 *  Created on: \date 12 septembre 2014
 *      Author: \author xelfe
 *  \brief : Fichier source de la classe LogManager
 */
#include "LogManager.h"

namespace Engine {

LogManager::LogManager() {
	initLogging("client.log");
	boost::log::add_common_attributes();
	boost::log::sources::severity_logger< severity_level > logMgr;

	BOOST_LOG_SEV(logMgr, normal) << "Message normal";
	BOOST_LOG_SEV(logMgr, warning) << "Message avertissement";
	BOOST_LOG_SEV(logMgr, critical) << "Message critique";
}

LogManager::~LogManager() {

}

void LogManager::initLogging(Ogre::String fileName) {
	
	boost::log::add_file_log(fileName);
}


} /* namespace Engine */