/*
 * \file EventListener.h
 *
 *  Created on: \date 2 ao�t 2014
 *      Author: \author joda
 *  \brief : Fichier d'en-tête de la classe de gestion d'évennements.
 */
#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_

#include "Event.h"

/*!
 * \namespace Engine
 * \brief Espace de nommage regroupant les dfférentes classes du moteur
 */
namespace Engine {

/*!
 * \class EventListener
 * \brief Classe d'écoute du gestionnaire d'évennements
 */
class EventListener {
public:
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe EngineListenner
	 *
	 */
	EventListener() {};

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe EngineListenner
	 *
	 */
	virtual ~EventListener() {};

	virtual void processEvent(Event* event) = 0;

};

} /* namespace Engine */

#endif /* EVENTLISTENER_H_ */
