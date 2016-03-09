/*
 * \file MessagePacket.cpp
 *
 *  Created on: \date 30 oct. 2014
 *      Author: \author joda
 *  \brief :
 */

#include "MessagePacket.h"

namespace Engine {

MessagePacket::MessagePacket() {
    opcode = 0;
    sousOpcode = 0;
    timestampDepart = boost::posix_time::microsec_clock::universal_time();

}

MessagePacket::~MessagePacket() {

}

int MessagePacket::getOpcode() {
    return opcode;
}

int MessagePacket::getSousOpcode() {
    return sousOpcode;
}

void MessagePacket::setOpcode(int opcode) {
    this->opcode = opcode;
}
void MessagePacket::setSousOpcode(int sousOpcode) {
    this->sousOpcode = sousOpcode;
}

boost::posix_time::ptime MessagePacket::getTimestampDepart() {
    return timestampDepart;
}

void MessagePacket::setTimestampDepart(boost::posix_time::ptime timestamp) {
    this->timestampDepart = timestamp;
}

boost::posix_time::ptime MessagePacket::getTimestampArriver() {
    return timestampArriver;
}

void MessagePacket::setTimestampArriver(boost::posix_time::ptime timestamp) {
    this->timestampArriver = timestamp;
}

} /* namespace Engine */
