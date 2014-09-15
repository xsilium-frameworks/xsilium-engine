/*
* \file LogManager.h
*
*  Created on: \date 12 septembre 2014
*      Author: \author xelfe
*  \brief : Fichier d'en-tête de la classe LogManager
*/
#ifndef LOGMANAGER_H_
#define LOGMANAGER_H_

/*!
* \namespace Engine
* \brief Espace de nommage regroupant les dfférentes classes du moteur.
*/
namespace Engine {

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

	};

} /* namespace Engine */
#endif /* LOGMANAGER_H_ */