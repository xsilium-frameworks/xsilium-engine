/*
 * \file GraphicsEntiteManager.h
 *
 *  Created on: \date 4 ao�t 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSENTITEMANAGER_H_
#define GRAPHICSENTITEMANAGER_H_

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
    GraphicsEntite * trouverEntite(int id);
    void deleteEntite(Ogre::String nom);

    void setSceneManager(Ogre::SceneManager* msceneMgr);

    void update(float time);

    void processEvent(Event * event);

    GraphicsEntite * getEntiteCurrentPlayer();

private:
    std::vector<GraphicsEntite *> listOfEntite;
    std::vector<GraphicsEntite *>::iterator entite;

    Ogre::SceneManager* msceneMgr;
};

} /* namespace Engine */

#endif /* GRAPHICSENTITEMANAGER_H_ */
