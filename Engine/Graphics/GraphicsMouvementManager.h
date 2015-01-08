/*
 * \file GraphicsMouvementManager.h
 *
 *  Created on: \date 8 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#ifndef ENGINE_GRAPHICS_GRAPHICSMOUVEMENTMANAGER_H_
#define ENGINE_GRAPHICS_GRAPHICSMOUVEMENTMANAGER_H_

#include "Event/Event.h"

namespace Engine {

/*
 *
 */
class GraphicsMouvementManager {
public:
	GraphicsMouvementManager();
	virtual ~GraphicsMouvementManager();

	void processEvent(Event * event);
};

} /* namespace Engine */

#endif /* ENGINE_GRAPHICS_GRAPHICSMOUVEMENTMANAGER_H_ */
