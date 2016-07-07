/*
 * EulerStdDevPacket.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: burghart
 */

#include <cassert>
#include <cstring>
#include <logx/Logging.h>
#include "EulerStdDevPacket.h"

LOGGING("EulerStdDevPacket")

EulerStdDevPacket::EulerStdDevPacket(const void* raw, uint length) {
  // Make sure our struct packs to the expected size to match the raw ANPP
  // packet
  assert(sizeof(_data) == _PACKET_DATA_LEN);

  // Unpack the header and set data validity time
  _initializeHeaderFromRaw(raw, length);
  assert(packetDataLen() == _PACKET_DATA_LEN);
  assert(packetId() == _PACKET_ID);

  // Copy the raw bytes after the header into our data struct
  memcpy(&_data, reinterpret_cast<const uint8_t *>(raw) + _HEADER_LEN, 
         _PACKET_DATA_LEN);

  // Set the data pointer
  _dataPtr = reinterpret_cast<uint8_t*>(&_data);
}

EulerStdDevPacket::~EulerStdDevPacket() {
}
