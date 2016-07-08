/*
 * SystemStatePacket.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: burghart
 */

#include <cassert>
#include <cstring>
#include <iomanip>
#include <logx/Logging.h>
#include "SystemStatePacket.h"

LOGGING("SystemStatePacket")

SystemStatePacket::SystemStatePacket(const void* raw, uint length) {
  // Make sure our struct packs to the expected size to match the raw ANPP
  // packet
  assert(sizeof(_data) == _PACKET_DATA_LEN);

  // Set _dataPtr to the address of our local _data struct
  _dataPtr = reinterpret_cast<uint8_t*>(&_data);

  // Initialize from the raw data
  _initializeFromRaw(raw, length);

  // Reset our own time of validity to the time contained in this packet.
  // We must overwrite the time set by _initializeFromRaw(), which used the
  // latest *previous* "time of validity" values.
  _setTimeOfValidity(_data._unixTimeSeconds, _data._microseconds);

  // Time of validity supplied in this packet applies to succeeding packets
  // as well. Save it in the static common location.
  _SetLatestTimeOfValidity(_data._unixTimeSeconds, _data._microseconds);

  DLOG << "System State packet - system status: 0x" <<
          std::setw(2) << std::setfill('0') << std::hex << _data._systemStatus <<
          ", filter status: 0x" <<
          std::setw(2) << std::setfill('0') << std::hex << _data._filterStatus;
}

SystemStatePacket::~SystemStatePacket() {
}

