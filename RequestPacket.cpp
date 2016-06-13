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
  ANPPPacket(raw, length, _PACKET_ID),
  _nRequestedPacketIds(packetDataLen()) {
  // Copy the raw bytes after the header into our list of requested packet IDs.
  // The packet length from the header tells us how many requested IDs there
  // are.
  memcpy(_requestedPacketIds, reinterpret_cast<const uint8_t *>(raw) + _HEADER_LEN, 
         _nRequestedPacketIds);
}

RequestPacket::RequestPacket(std::vector<uint8_t> idList) :
  ANPPPacket(_PACKET_ID, idList.size()) {
  // It's a problem if they request more that 255 packet ids...
  assert(idList.size() <= 255);
  
  // Copy the IDs into _requestedPacketIds
  _nRequestedPacketIds = idList.size();
  memcpy(_requestedPacketIds, idList.data(), _nRequestedPacketIds);
  
  // Update the CRC and LRC in the header to reflect the changes above.
  _updateHeader();
}

RequestPacket::~RequestPacket() {
}
