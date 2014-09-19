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

	/*!
	 * \enum severity_level
	 * \brief Constantes des niveaux de message.
	 */
	enum severity_level {
		normal,			/*!< Niveau 1. */
		notification,	/*!< Niveau 2. */
		warning,		/*!< Niveau 3. */
		error,			/*!< Niveau 4. */
		critical,		/*!< Niveau 5. */
		ogre,			/*!< Niveau 6. */
		cegui			/*!< Niveau 7. */
	};

	BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level);

	/*!
	 * \class LogManager
	 * \brief Classe gestionnaire de log.
	 *
	 * Classe permettant de gèrer les différentes niveaux de log selon la configuration de compile.
	 *
	 */
	class LogManager : Singleton<LogManager>, Ogre::LogListener, CEGUI::Logger {

		friend class Engine::Singleton<LogManager> ;

	public:
		/*!
		*  \brief Constructeur
		*
		*  Constructeur de la classe LogManager
		*
		*/
		LogManager();

		/*!
		*  \brief Destructeur
		*
		*  Constructeur de la classe LogManager
		*
		*/
		virtual ~LogManager();

		Ogre::LogManager* ogreLogManager;

		void initOgreLog();

		/*!
		*  \brief Méthode qui configure le nom du fichier .log
		*
		*  \param[in] fileName : String de nom du fichier de log
		*/
		void setFileLog(Ogre::String fileName);

		/*!
		*  \brief Méthode qui configure un message vers LogManager
		*
		*  \param[in] logMessage : String de message a ajouter vers LogManager
		*  \param[in] logLevel : String de niveau du message a ajouter vers LogManager
		*/
		void setLogMessage(Ogre::String logMessage, Ogre::String logLevel);

		/*!
		*  \brief Méthode derive de Ogre::Log
		*
		*  Méthode derive de Ogre::Log qui est appellé à chaque message gèré par ogre
		*
		*  \param[in] message : String de message envoyé par Ogre::Log
		*  \param[in] lml : String de nom du niveau du message envoyé par Ogre::Log
		*  \param[in] maskDebug : bool pour masquer les messages specific au mode debug
		*  \param[in] skipThisMessage : bool pour designer si un message doit etre ignoré
		*
		*/
		void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage);

		/*!
		*  \brief Méthode derive de CEGUI::Log
		*
		*  Méthode derive de CEGUI::Log qui est appellé à chaque message gèré par cegui
		*
		*  \param[in] message : String de message envoyé par CEGUI::Log
		*  \param[in] level : String du nom de niveau du message envoyé par CEGUI::Log
		*/
		void logEvent(const CEGUI::String &message, CEGUI::LoggingLevel level);

		/*!
		*  \brief Méthode derive de CEGUI::Log qui configure le nom du fichier .log
		*
		*  \param[in] fileName : String de nom du fichier de log
		*  \param[in] append : bool
		*/
		void setLogFilename(const CEGUI::String &filename, bool append);

	};

} /* namespace Engine */
#endif /* LOGMANAGER_H_ */
