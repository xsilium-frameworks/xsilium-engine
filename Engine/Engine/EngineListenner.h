/*
 * \file EngineListenner.h
 *
 *  Created on: \date 2 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef ENGINELISTENNER_H_
#define ENGINELISTENNER_H_

#include "Event/Event.h"

namespace Engine {



/*
 *
 */

class EngineListenner {
public:
	EngineListenner() {};
	virtual ~EngineListenner() {};
	virtual void processEvent(Event * event) = 0;
	virtual void shutdown() = 0;

};

} /* namespace Engine */



#endif /* ENGINELISTENNER_H_ */
