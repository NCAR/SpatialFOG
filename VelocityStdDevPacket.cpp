/*
 * VelocityStdDevPacket.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: burghart
 */

#include <cassert>
#include <cstring>
#include <logx/Logging.h>
#include "VelocityStdDevPacket.h"

LOGGING("VelocityStdDevPacket")

VelocityStdDevPacket::VelocityStdDevPacket(const void* raw, uint length) {
  // Make sure our struct packs to the expected size to match the raw ANPP
  // packet
  assert(sizeof(_data) == _PACKET_DATA_LEN);

  // Set _dataPtr to the address of our local _data struct
  _dataPtr = reinterpret_cast<uint8_t*>(&_data);

  // Initialize from the raw data
  _initializeFromRaw(raw, length);

  // Validate the packet data length
  if (packetDataLen() != _PACKET_DATA_LEN) {
      std::ostringstream oss;
      oss << "Packet data length " << packetDataLen() <<
             " is invalid for VelocityStdDevPacket";
      throw BadHeader(oss.str());
  }
}

VelocityStdDevPacket::~VelocityStdDevPacket() {
}
