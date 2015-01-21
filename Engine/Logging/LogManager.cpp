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

		initOgreLog();

	}

	LogManager::~LogManager() {
		Ogre::LogManager::getSingleton().getDefaultLog()->removeListener(this);
	}

	void LogManager::initOgreLog() {
		Ogre::LogManager* ogreLogManager = new Ogre::LogManager();
		ogreLogManager->getSingleton().createLog("OgreLogfile.log", true, true, true);
		ogreLogManager->getSingleton().getDefaultLog()->addListener(this);

	}

	void LogManager::initLog(Ogre::String fileName) {

		// Definition et creation des attributs du log
		boost::log::add_file_log(
			boost::log::keywords::file_name = *Engine::getInstance()->getResourcePath() + fileName + "_%N.log",
			// rotation des logs a chaque 1 mo
			boost::log::keywords::rotation_size = 1 * 1024 * 1024,
			// rotation des logs a minuit
			boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
			//Definition des attributs du log
			boost::log::keywords::format = boost::log::expressions::stream
			// Affichage du level
			<< "<LEVEL " << severity << "> "
			// Personalisation du TimeStamp
			<< "[" << boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M") << "] "
			// Affichage du message
			<< boost::log::expressions::message
			);

		// Ajoutes les attributs 
		boost::log::add_common_attributes();
		boost::log::sources::severity_logger< severity_level > logMgr;
		setLogMessage("######## Initialisation du LogManager ########", NOTIFICATION);
	}

	void LogManager::setLogMessage(Ogre::String logMessage, severity_level logLevel) {
		boost::log::sources::severity_logger< severity_level > logMgr;
		BOOST_LOG_SEV(logMgr, logLevel) << logMessage;
	}

	// Listener event log de ogre
	void LogManager::messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage) {
		boost::log::sources::severity_logger< severity_level > logMgr;
		BOOST_LOG_SEV(logMgr, OGRE) << message;
	}

	// Listener event log de cegui
	void LogManager::logEvent(const CEGUI::String &message, CEGUI::LoggingLevel level) {
		boost::log::sources::severity_logger< severity_level > logMgr;
		BOOST_LOG_SEV(logMgr, CEGUI) << message;
	}

	// Listener nom de fichier de cegui 
	void LogManager::setLogFilename(const CEGUI::String &filename, bool append) {

	}


} /* namespace Engine */
