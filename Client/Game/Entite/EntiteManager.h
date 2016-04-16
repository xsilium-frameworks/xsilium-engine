/*
 * EntiteManager.h
 *
 *  Created on: 11 avr. 2016
 *      Author: joda
 */

#ifndef CLIENT_GAME_ENTITE_ENTITEMANAGER_H_
#define CLIENT_GAME_ENTITE_ENTITEMANAGER_H_

#include <Network/NetworkManager.h>
#include <Event/EventManager.h>

class EntiteManager: public Engine::NetworkListener {
public:
    EntiteManager();
    virtual ~EntiteManager();

    void run();

    void processPacket(Engine::MessagePacket * messagePacket);

    void processEvent(Event * event);

private:
    Engine::NetworkManager * networkManager;
};

#endif /* CLIENT_GAME_ENTITE_ENTITEMANAGER_H_ */
