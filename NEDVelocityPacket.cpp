/*
 * NEDVelocityPacket.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: burghart
 */

#include <cassert>
#include <cstring>
#include <logx/Logging.h>
#include "NEDVelocityPacket.h"

LOGGING("NEDVelocityPacket")

NEDVelocityPacket::NEDVelocityPacket(const void* raw, uint length) :
  ANPPPacket(raw, length, _PACKET_ID, _PACKET_DATA_LEN) {
  // Make sure our _data struct is the correct size and copy the raw 
  assert(sizeof(_data) == _PACKET_DATA_LEN);
  // Copy the raw bytes after the header into our data struct
  memcpy(&_data, reinterpret_cast<const uint8_t *>(raw) + _HEADER_LEN, 
         _PACKET_DATA_LEN);
}

NEDVelocityPacket::~NEDVelocityPacket() {
}
