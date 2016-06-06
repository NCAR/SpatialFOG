/*
 * RequestPacket.cpp
 *
 *  Created on: Jun 2, 2016
 *      Author: burghart
 */

#include <cstring>
#include <sstream>
#include <logx/Logging.h>
#include "RequestPacket.h"

LOGGING("RequestPacket")

RequestPacket::RequestPacket(const void* raw, uint length) :
  ANPPPacket(raw, length, PACKET_ID),
  _nRequestedPacketIds(packetDataLen()) {
  // Copy the raw bytes after the header into our list of requested packet IDs.
  // The packet length from the header tells us how many requested IDs there
  // are.
  memcpy(_requestedPacketIds, reinterpret_cast<const uint8_t *>(raw) + HEADER_LEN, 
         _nRequestedPacketIds);
}

RequestPacket::~RequestPacket() {
}
