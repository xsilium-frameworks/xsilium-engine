/*
 * \file ControleInterface.h
 *
 *  Created on: \date 4 nov. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef CONTROLEINTERFACE_H_
#define CONTROLEINTERFACE_H_

#include "EventManager/Event/Event.h"

enum EventInterface
{
	NOTIFICATION = 0,
	LOGIN,
	CHARGEMENT,
	MESSAGE
};

enum ActionInterface
{
	ACTIVE = 0,
	DESACTIVE,
	VISIBLE,
	INVISIBLE
};

enum RetourInterface
{
	CANCELBOUTON = 0,
	OKBOUTON
};



/*
 *
 */
class ControleInterface {
public:
	ControleInterface() {};
	virtual ~ControleInterface() {};

	virtual void retourInterface(EventInterface eventInterface,int retour) = 0;


	bool checkRegistreEvent(EventInterface * eventInterface)
	{
		for (std::vector<EventInterface>::iterator it =EventEnregistre.begin() ; it!=EventEnregistre.end() ; ++it)
		{
			if (*it == *eventInterface)
			{
				return true;
			}
		}
		return false;
	};

	Event * activeInterface()
	{
		Event * event = new Event();
		//event->setProperty("eventType",ACTIVE);
		return event;
	};

	Event * deactiveInterface()
	{
		Event * event = new Event();
		//event->setProperty("eventType",DESACTIVE);
		return event;
	};

	Event * visibleInterface()
	{
		Event * event = new Event();
		//event->setProperty("eventType",VISIBLE);
		return event;
	};

	Event * invisibleInterface()
	{
		Event * event = new Event();
		//event->setProperty("eventType",INVISIBLE);
		return event;
	};




protected:
	std::vector<EventInterface> EventEnregistre;
};

#endif /* CONTROLEINTERFACE_H_ */
