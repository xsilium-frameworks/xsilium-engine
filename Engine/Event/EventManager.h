/*
* \file EventManager.h
*
*  Created on: \date 10 mars 2013
*      Author: \author joda
*  \brief : Fichier d'en-tête de la classe de gestion d'évennements.
*/

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include <queue>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include "Event.h"

/*!
* \namespace Engine
* \brief Espace de nommage regroupant les dfférentes classes du moteur.
*/
namespace Engine {

	/*!
	* \class EventManager
	* \brief Classe gestionnaire d'évennements.
	*
	* Classe permettant de gèrer les évennements.
	*
	*/
	class EventManager {
	public:
		/*!
		*  \brief Constructeur.
		*
		*  Constructeur de la classe EventManager.
		*
		*/
		EventManager();

		/*!
		*  \brief Destructeur.
		*
		*  Destructeur abstrait de la classe EventManager.
		*
		*/
		virtual ~EventManager();

		/*!
		*
		* \brief Ajoute un évennement .
		*
		* \param event : Évennement.
		*/
		void addEvent(Event event);

		/*!
		*
		* \brief Obtention des évennements.
		*
		* \return Liste des évennements.
		*/
		Event* getEvent();

		/*!
		*
		* \brief Suppression du premier event.
		*
		*/
		void deleteEvent();

		/*!
		*
		* \brief Verification afin de déterminer si la liste est vide.
		*
		* \return true si la liste est vide.
		*/
		bool isEmpty();

		virtual void processEvent(Event* event) = 0;


	private:
		std::queue<Event> listOfEvent;
		boost::mutex mutexList;


	};

} /* namespace Engine */

#endif /* EVENTMANAGER_H_ */
