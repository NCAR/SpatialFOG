/*
 * ANPPPacketFactory.cpp
 *
 *  Created on: Jun 1, 2016
 *      Author: burghart
 */

#include "ANPPPacketFactory.h"

// Pointer to our singleton instance, which is instantiated at first use.
ANPPPacketFactory * ANPPPacketFactory::_instancePtr = 0;

ANPPPacketFactory::ANPPPacketFactory() {
}

ANPPPacketFactory::~ANPPPacketFactory() {
}

