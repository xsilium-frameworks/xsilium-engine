/*
 * \file EngineListenner.h
 *
 *  Created on: \date 2 ao�t 2014
 *      Author: \author joda
 *  \brief : Fichier d'en-tête de la classe de gestion d'évennements.
 */
#ifndef ENGINELISTENNER_H_
#define ENGINELISTENNER_H_

#include "Event/EventManager.h"
#include "Singleton/Singleton.h"

/*!
 * \namespace Engine
 * \brief Espace de nommage regroupant les dfférentes classes du moteur
 */
namespace Engine {

/*!
 * \class EngineListener
 * \brief Classe d'écoute du gestionnaire d'évennements
 */
class EngineListenner: public EventManager {
public:
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe EngineListenner
	 *
	 */
	EngineListenner() {
	}
	;

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe EngineListenner
	 *
	 */
	virtual ~EngineListenner() {
	}
	;
	virtual void processEvent(Event * event) = 0;
	virtual void exit() = 0;

};

} /* namespace Engine */



#endif /* ENGINELISTENNER_H_ */
