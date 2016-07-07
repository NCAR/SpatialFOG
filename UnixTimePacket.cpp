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

UnixTimePacket::UnixTimePacket(const void* raw, uint length) {
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

  // Reset our own time of validity to the time contained in this packet.
  // We must overwrite the time set by _initializeFromRaw(), which used the
  // latest *previous* "time of validity" values.
  _setTimeOfValidity(_data._unixTimeSeconds, _data._microseconds);

  // Time of validity supplied in this packet applies to succeeding packets
  // as well. Save it in the static common location.
  _SetLatestTimeOfValidity(_data._unixTimeSeconds, _data._microseconds);
}

UnixTimePacket::~UnixTimePacket() {
}

