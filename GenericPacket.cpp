/*
 * GenericPacket.cpp
 *
 *  Created on: Jul 6, 2016
 *      Author: burghart
 */

#include <cstring>
#include <sstream>
#include <logx/Logging.h>
#include "GenericPacket.h"

LOGGING("GenericPacket")

GenericPacket::GenericPacket(const void* raw, uint length) {
  // Set _dataPtr to the address of our local _data struct
  _dataPtr = reinterpret_cast<uint8_t*>(&_data);

  // Initialize from the raw data
  _initializeFromRaw(raw, length);
}

GenericPacket::~GenericPacket() {
}

