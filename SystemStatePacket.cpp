/*
 * SystemStatePacket.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: burghart
 */

#include <cassert>
#include <cstring>
#include "SystemStatePacket.h"

SystemStatePacket::SystemStatePacket(const void* raw, uint length) :
  ANPPPacket(raw, length, _PACKET_ID, _PACKET_DATA_LEN) {
  assert(sizeof(_data) == _PACKET_DATA_LEN);
  // Copy the raw bytes after the header into our data struct
  memcpy(&_data, reinterpret_cast<const uint8_t *>(raw) + _HEADER_LEN, 
         _PACKET_DATA_LEN);
}

SystemStatePacket::~SystemStatePacket() {
}

