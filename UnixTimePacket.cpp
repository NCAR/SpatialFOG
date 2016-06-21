/*
 * UnixTimePacket.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: burghart
 */

#include <cassert>
#include <cstring>
#include <logx/Logging.h>
#include "UnixTimePacket.h"

LOGGING("UnixTimePacket")

UnixTimePacket::UnixTimePacket(const void* raw, uint length) :
  ANPPPacket(raw, length, _PACKET_ID, _PACKET_DATA_LEN) {
  // Make sure our _data struct is the correct size and copy the raw 
  assert(sizeof(_data) == _PACKET_DATA_LEN);

  // Copy the raw bytes after the header into our data struct
  memcpy(&_data, reinterpret_cast<const uint8_t *>(raw) + _HEADER_LEN, 
         _PACKET_DATA_LEN);

  // Set the data pointer
  _dataPtr = reinterpret_cast<uint8_t*>(&_data);

  // Update the header LRC and CRC to reflect the new data contents
  _updateHeader();

  // Time of validity supplied in this packet applies to succeeding packets
  // as well. Save it in a static common location.
  _SetLatestTimeOfValidity(_data._unixTimeSeconds, _data._microseconds);

  // Reset our own time of validity. We must overwrite the time set by
  // our superclass constructor, which used the latest *previous* "time of
  // validity" values.
  _setTimeOfValidity(_data._unixTimeSeconds, _data._microseconds);
}

UnixTimePacket::~UnixTimePacket() {
}

