/*
 * \file GuiListenner.h
 *
 *  Created on: \date 2 sept. 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GUILISTENNER_H_
#define GUILISTENNER_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "Gui/GuiManager.h"
#include "Event/Event.h"

namespace Engine {

class GuiManager;

/*
 *
 */
class GuiListenner {
public:
	GuiListenner();
	virtual ~GuiListenner();

	virtual void processEvent(Event* event) = 0;

	virtual void initGui() = 0;

protected:
	CEGUI::Window* parent;

};

} /* namespace Engine */

#endif /* GUILISTENNER_H_ */
