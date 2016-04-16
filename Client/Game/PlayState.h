/*
 * \file PlayStater.h
 *
 *  Created on: \date 24 septembre 2014
 *      Author: \author xelfe
 *  \brief : Fichier d'en-t�te de la classe PlayState
 */
#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState/GameState.h"
#include "Logging/LogManager.h"
#include "Chat/GestionnaireChat.h"
#include "Entite/EntiteManager.h"

class PlayState: public GameState {
public:
    PlayState();
    virtual ~PlayState();

    void enter();
    void createScene();

    void exit();

    void update(double timeSinceLastFrame);

    void processEvent(Event * event);

private:
    GestionnaireChat * gestionnaireChat;
    EntiteManager * entiteManager;

};

#endif /* PLAY_STATE_H */
