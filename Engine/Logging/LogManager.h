/*
* \file LogManager.h
*
*  Created on: \date 12 septembre 2014
*      Author: \author xelfe
*  \brief : Fichier d'en-tête de la classe LogManager
*/
#ifndef LOGMANAGER_H_
#define LOGMANAGER_H_

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include "Engine/Engine.h"

/*!
* \namespace Engine
* \brief Espace de nommage regroupant les dfférentes classes du moteur.
*/
namespace Engine {

	enum severity_level
	{
		normal,
		notification,
		warning,
		error,
		critical
	};

	/*!
	* \class LogManager
	* \brief Classe gestionnaire de log.
	*
	* Classe permettant de gèrer les différentes niveaux de log selon la configuration de compile.
	*
	*/
	class LogManager  {
	public:
		LogManager();
		virtual ~LogManager();

		void initLogging(Ogre::String fileName);


	};

} /* namespace Engine */
#endif /* LOGMANAGER_H_ */