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

RequestPacket::RequestPacket(uint8_t id) :
  ANPPPacket(_PACKET_ID, 1) {
  // Our list of requested packet IDs has only one element
  _nRequestedPacketIds = 1;
  _requestedPacketIds[0] = id;

  // Set the data pointer
  _dataPtr = reinterpret_cast<uint8_t*>(_requestedPacketIds);

  // Update the header LRC and CRC to reflect the new data contents
  _updateHeader();
}

RequestPacket::RequestPacket(std::vector<uint8_t> idList) :
  ANPPPacket(_PACKET_ID, idList.size()) {
  // It's a problem if they request more that 255 packet ids...
  assert(idList.size() <= 255);

  // Copy the IDs into _requestedPacketIds
  _nRequestedPacketIds = idList.size();
  memcpy(_requestedPacketIds, idList.data(), _nRequestedPacketIds);

  // Set the data pointer
  _dataPtr = reinterpret_cast<uint8_t*>(_requestedPacketIds);

  // Update the header LRC and CRC to reflect the new data contents
  _updateHeader();
}

RequestPacket::~RequestPacket() {
}
