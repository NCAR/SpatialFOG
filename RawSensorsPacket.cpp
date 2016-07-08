/*
 * RawSensorsPacket.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: burghart
 */

#include <cassert>
#include <cstring>
#include <logx/Logging.h>
#include "RawSensorsPacket.h"

LOGGING("RawSensorsPacket")

RawSensorsPacket::RawSensorsPacket(const void* raw, uint length) {
  // Make sure our struct packs to the expected size to match the raw ANPP
  // packet
  assert(sizeof(_data) == _PACKET_DATA_LEN);

  // Set _dataPtr to the address of our local _data struct
  _dataPtr = reinterpret_cast<uint8_t*>(&_data);

  // Initialize from the raw data
  _initializeFromRaw(raw, length);
}

RawSensorsPacket::~RawSensorsPacket() {
}
