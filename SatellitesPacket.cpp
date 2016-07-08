/*
 * SatellitesPacket.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: burghart
 */

#include <cassert>
#include <cstring>
#include <logx/Logging.h>
#include "SatellitesPacket.h"

LOGGING("SatellitesPacket")

SatellitesPacket::SatellitesPacket(const void* raw, uint length) {
  // Make sure our struct packs to the expected size to match the raw ANPP
  // packet
  assert(sizeof(_data) == _PACKET_DATA_LEN);

  // Set _dataPtr to the address of our local _data struct
  _dataPtr = reinterpret_cast<uint8_t*>(&_data);

  // Initialize from the raw data
  _initializeFromRaw(raw, length);

  DLOG << "Satellites packet - GPS: " << uint(_data._nGps) <<
          ", SBAS: " << uint(_data._nSbas) <<
          ", GLONASS: " << uint(_data._nGlonass) <<
          ", BeiDou: " << uint(_data._nBeiDou);
}

SatellitesPacket::~SatellitesPacket() {
}
