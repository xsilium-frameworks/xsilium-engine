/*
 * \file GraphicsMouvementManager.cpp
 *
 *  Created on: \date 8 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsMouvementManager.h"

namespace Engine {

GraphicsMouvementManager::GraphicsMouvementManager() {
    graphicsCamera = 0;
    graphicsEntiteManager = 0;
    direction = Ogre::Vector3::ZERO;
    deplacement = false;
    newDirection = false;
    clickLeft = false;
    clickRight = false;
}

GraphicsMouvementManager::~GraphicsMouvementManager() {
    InputManager::getInstance()->removeMouseListener(this);
}

void GraphicsMouvementManager::setGraphicsCamera(GraphicsCamera * graphicsCamera) {
    this->graphicsCamera = graphicsCamera;
    InputManager::getInstance()->addMouseListener(this, "MouvementManager");
}

void GraphicsMouvementManager::setGraphicsEntiteManager(
        GraphicsEntiteManager*& graphicsEntiteManager) {
    this->graphicsEntiteManager = graphicsEntiteManager;
}

void GraphicsMouvementManager::processEvent(Event * event) {
    if (event->hasProperty("Keyboard")) {
        if ((event->getProperty("Fonction").compare("AVANCER")) == 0) {
            if (atoi(event->getProperty("Action").c_str()) == 1) {
                direction.x = 1;
            } else {
                direction.x = 0;
            }
            newDirection = true;
        }

        if ((event->getProperty("Fonction").compare("DROITE")) == 0) {
            if (atoi(event->getProperty("Action").c_str()) == 1) {
                direction.z = 1;
            } else {
                direction.z = 0;
            }
            newDirection = true;
        }

        if ((event->getProperty("Fonction").compare("GAUCHE")) == 0) {
            if (atoi(event->getProperty("Action").c_str()) == 1) {
                direction.z = -1;
            } else {
                direction.z = 0;
            }
            newDirection = true;
        }

        if ((event->getProperty("Fonction").compare("RECULER")) == 0) {
            if (atoi(event->getProperty("Action").c_str()) == 1) {
                direction.x = -1;
            } else {
                direction.x = 0;
            }
            newDirection = true;
        }

        if ((event->getProperty("Fonction").compare("SAUTE")) == 0) {
            if (atoi(event->getProperty("Action").c_str()) == 1) {
                direction.y = 1;
            } else {
                direction.y = 0;
            }
            newDirection = true;
        }
    }
}

void GraphicsMouvementManager::update(double timeSinceLastFrame) {
    if (newDirection && deplacement) {

        Ogre::Vector3 mGoalDirection = Ogre::Vector3::ZERO;

        if (clickLeft) {
            mGoalDirection += direction.x
                    * graphicsCamera->getPPitchNode()->getOrientation().xAxis();
            mGoalDirection += direction.z
                    * graphicsCamera->getPPitchNode()->getOrientation().zAxis();
            mGoalDirection.normalise();
        } else {
            mGoalDirection = direction;
        }

        //mise a jour des deplacements du perso .
        GraphicsEntite * graphicsEntite = graphicsEntiteManager->getEntiteCurrentPlayer();

        if (graphicsEntite) {
            graphicsEntite->deplaceEntite(mGoalDirection);
        }

        if (graphicsCamera) {
            graphicsCamera->setPosition(mGoalDirection);
        }

        Event event;
        event.setProperty("MouvementManager", 1);
        event.setProperty("X", mGoalDirection.x);
        event.setProperty("Y", mGoalDirection.y);
        event.setProperty("Z", mGoalDirection.z);
        EventManager::getInstance()->addEvent(event);

        newDirection = false;

    }

}

bool GraphicsMouvementManager::mouseMoved(const OIS::MouseEvent &e) {
    if (deplacement) {
        if (graphicsCamera)
            graphicsCamera->injectMouseMove(e);
    }
    return true;
}
bool GraphicsMouvementManager::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {

    if (id == OIS::MB_Left)
        clickLeft = true;

    if (id == OIS::MB_Right)
        clickRight = true;

    return true;
}
bool GraphicsMouvementManager::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {

    if (id == OIS::MB_Left)
        clickLeft = false;

    if (id == OIS::MB_Right)
        clickRight = false;
    return true;
}

void GraphicsMouvementManager::activeMouvement() {
    deplacement = true;
}
void GraphicsMouvementManager::deactiveMouvement() {
    deplacement = false;
}

} /* namespace Engine */
