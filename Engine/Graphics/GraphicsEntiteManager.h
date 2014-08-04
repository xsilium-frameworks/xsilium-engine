/*
 * \file GraphicsEntiteManager.h
 *
 *  Created on: \date 4 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSENTITEMANAGER_H_
#define GRAPHICSENTITEMANAGER_H_

#include "Event/Event.h"
#include "GraphicsEntite.h"
#include <vector>

namespace Engine {

/*
 *
 */
class GraphicsEntiteManager {
public:
	GraphicsEntiteManager();
	virtual ~GraphicsEntiteManager();

	void createEntite(Event * event);
	//Entite * trouverEntite(std::string nom);


	void update(float time);




private:
	std::vector<GraphicsEntite *> listOfEntite ;
	std::vector<GraphicsEntite *>::iterator entite ;
};

} /* namespace Engine */

#endif /* GRAPHICSENTITEMANAGER_H_ */
