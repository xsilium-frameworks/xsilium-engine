/*
 * \file LogManager.h
 *
 *  Created on: \date 12 septembre 2014
 *      Author: \author xelfe
 *  \brief : Fichier d'en-t�te de la classe LogManager
 */
#ifndef LOGMANAGER_H_
#define LOGMANAGER_H_

#include <OgreLogManager.h>
#include <CEGUI/Logger.h>
#include <Singleton/Singleton.h>

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
 * \brief Espace de nommage regroupant les dff�rentes classes du moteur.
 */
namespace Engine {

	/*!
	 * \enum severity_level
	 * \brief Constantes des niveaux de message.
	 */
	enum severity_level {
		NORMAL,				/*!< Niveau 1. */
		NOTIFICATION,		/*!< Niveau 2. */
		AVERTISSEMENT,		/*!< Niveau 3. */
		OGRE,				/*!< Niveau 4. */
		CEGUI,				/*!< Niveau 5. */
		ERREUR,				/*!< Niveau 6. */
		CRITIQUE			/*!< Niveau 7. */

	};

	BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level);

	/*!
	 * \class LogManager
	 * \brief Classe gestionnaire de log.
	 *
	 * Classe permettant de g�rer les diff�rentes niveaux de log selon la configuration de compile.
	 *
	 */
	class LogManager : public Singleton<LogManager>, Ogre::LogListener, CEGUI::Logger {

#ifdef _WIN32
        friend class Singleton < LogManager > ;

#else
        friend class Engine::Singleton<LogManager> ;
#endif

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
		*  \brief M�thode qui initiliase LogManager
		*
		*  \param[in] fileName : String de nom du fichier de log
		*/
		void initLog(std::string mResourcePath,std::string fileName);

		/*!
		*  \brief M�thode qui configure un message vers LogManager
		*
		*  \param[in] logMessage : String de message a ajouter vers LogManager
		*  \param[in] logLevel : String de niveau du message a ajouter vers LogManager
		*/
		void setLogMessage(Ogre::String logMessage, severity_level logLevel);

		/*!
		*  \brief M�thode derive de Ogre::Log
		*
		*  M�thode derive de Ogre::Log qui est appell� � chaque message g�r� par ogre
		*
		*  \param[in] message : String de message envoy� par Ogre::Log
		*  \param[in] lml : String de nom du niveau du message envoy� par Ogre::Log
		*  \param[in] maskDebug : bool pour masquer les messages specific au mode debug
		*  \param[in] skipThisMessage : bool pour designer si un message doit etre ignor�
		*
		*/
		void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage);

		/*!
		*  \brief M�thode derive de CEGUI::Log
		*
		*  M�thode derive de CEGUI::Log qui est appell� � chaque message g�r� par cegui
		*
		*  \param[in] message : String de message envoy� par CEGUI::Log
		*  \param[in] level : String du nom de niveau du message envoy� par CEGUI::Log
		*/
		void logEvent(const CEGUI::String &message, CEGUI::LoggingLevel level);

		/*!
		*  \brief M�thode derive de CEGUI::Log qui configure le nom du fichier .log
		*
		*  \param[in] fileName : String de nom du fichier de log
		*  \param[in] append : bool
		*/
		void setLogFilename(const CEGUI::String &filename, bool append);

	private:
		boost::log::sources::severity_logger< severity_level > logMgr;

	};

} /* namespace Engine */
#endif /* LOGMANAGER_H_ */
