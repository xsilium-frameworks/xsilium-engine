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
#include "EventListener.h"
#include <Singleton/Singleton.h>
#include <Ogre.h>

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
class EventManager : public Singleton<EventManager> , public Ogre::FrameListener {

	friend class Singleton<EventManager> ;
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
	 * \brief Init du EventManager .
	 *
	 * \param event : Évennement.
	 */
	void init(Ogre::Root*	m_pRoot);

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

	/*!
	 *
	 * \brief Ajoute un nouveau listener
	 *
	 */
	void addListenneur(EventListener * eventListener);
	/*!
	 *
	 * \brief supprime tout les listener
	 *
	 */

	void removeAllListenneur();
	/*!
	 *
	 * \brief appel les listener
	 *
	 * \return true si la liste est vide.
	 */
	void callback(Event * event = 0);

	bool frameStarted(const Ogre::FrameEvent& m_FrameEvent);
	bool frameRenderingQueued(const Ogre::FrameEvent& m_FrameEvent);
	bool frameEnded(const Ogre::FrameEvent& m_FrameEvent);


private:
	std::queue<Event> listOfEvent;
	boost::mutex mutexList;

	std::vector<EventListener*> listOfEventListener;

	Ogre::Root*	m_pRoot;


};

} /* namespace Engine */

#endif /* EVENTMANAGER_H_ */
