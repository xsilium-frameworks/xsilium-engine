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

//		m_pLog = 0;
		Ogre::LogManager* ogreLogManager = new Ogre::LogManager();
		ogreLogManager->getSingleton().createLog("OgreLogfile.log", true, true, true);
		ogreLogManager->getSingleton().getDefaultLog()->addListener(this);
	//	m_pLog->setDebugOutputEnabled(true);

		
		
		initLogging("client");

		boost::log::add_common_attributes();
		boost::log::sources::severity_logger< severity_level > logMgr;

		BOOST_LOG_SEV(logMgr, notification) << "######## Initialisation du LogManager ########";

		BOOST_LOG_SEV(logMgr, normal) << "Message niveau normal";
		BOOST_LOG_SEV(logMgr, warning) << "Message niveau avertissement";
		BOOST_LOG_SEV(logMgr, critical) << "Message niveau critique";
	}

	LogManager::~LogManager() {
		Ogre::LogManager::getSingleton().getDefaultLog()->removeListener(this);
	}

	void LogManager::messageLogged( const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage )
	{
		boost::log::sources::severity_logger< severity_level > logMgr;
		BOOST_LOG_SEV(logMgr, normal) << message ;
		
	}

	void LogManager::initLogging(Ogre::String fileName) {

		
		//boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");
		boost::log::add_file_log
			(
			boost::log::keywords::file_name = fileName + "_%N.log",
			// rotation des logs a chaque 1 mo
			boost::log::keywords::rotation_size = 1 * 1024 * 1024,
			// rotation des logs a minuit
			boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),

			boost::log::keywords::format = boost::log::expressions::stream
			<< "<LEVEL " << severity << "> "
			// Personalisation du TimeStamp
			<< "[" << boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M") << "] "
			<< boost::log::expressions::message

			);
	}


} /* namespace Engine */
