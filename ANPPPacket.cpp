/*
 * ANPPPacket.cpp
 *
 *  Created on: Jun 1, 2016
 *      Author: burghart
 */

#include "ANPPPacket.h"

ANPPPacket::ANPPPacket(std::vector<uint8_t> data) {
  // We must have at least 5 bytes (the header length)
  if (data.size() < 5) {
    throw BadPacketData("Packet data too short for valid ANPP packet");
  }
  
  // Check the header to see if the LRC matches the contents
  if (! IsValidHeader(data.data())) {
    throw BadPacketData("Header LRC does not match header contents");
  }
}

ANPPPacket::~ANPPPacket() {
}

