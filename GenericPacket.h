/*
 * GenericPacket.h
 *
 *  Created on: Jul 6, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_GENERICPACKET_H_
#define SRC_SPATIALFOG_GENERICPACKET_H_

#include "AnppPacket.h"

class GenericPacket: public AnppPacket {
public:
    GenericPacket(const void* raw, uint32_t length);
    virtual ~GenericPacket();
private:
    uint8_t _data[255];
};

#endif /* SRC_SPATIALFOG_GENERICPACKET_H_ */
