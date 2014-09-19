/*
 * \file LogManager.h
 *
 *  Created on: \date 12 septembre 2014
 *      Author: \author xelfe
 *  \brief : Fichier d'en-tête de la classe LogManager
 */
#ifndef LOGMANAGER_H_
#define LOGMANAGER_H_

#include "Engine/Engine.h"
#include <OgreLogManager.h>
#include <CEGUI/Logger.h>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/support/date_time.hpp>

/*!
 * \namespace Engine
 * \brief Espace de nommage regroupant les dfférentes classes du moteur.
 */
namespace Engine {

enum severity_level {
	normal,
	notification,
	warning,
	error,
	critical,
	ogre,
	cegui
};

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level);

/*!
 * \class LogManager
 * \brief Classe gestionnaire de log.
 *
 * Classe permettant de gèrer les différentes niveaux de log selon la configuration de compile.
 *
 */
class LogManager : public Engine::Singleton<LogManager> , Ogre::LogListener, CEGUI::Logger {

	friend class Engine::Singleton<LogManager> ;

public:
	LogManager();
	virtual ~LogManager();

	Ogre::LogManager* ogreLogManager;

	void initOgreLog();
	void setFileLog(Ogre::String fileName);
	void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage);
	void logEvent(const CEGUI::String &message, CEGUI::LoggingLevel level);
	void setLogFilename(const CEGUI::String &filename, bool append);

};

} /* namespace Engine */
#endif /* LOGMANAGER_H_ */
