/*
 * DetailedSatellitesPacket.cpp
 *
 *  Created on: Sep 22, 2016
 *      Author: Chris Burghart <burghart@ucar.edu>
 */

#include <cassert>
#include <cstring>
#include <logx/Logging.h>
#include "DetailedSatellitesPacket.h"

LOGGING("DetailedSatellitesPacket")

DetailedSatellitesPacket::DetailedSatellitesPacket(const void* raw, uint length) {
  // Make sure our struct packs to the expected size to match the raw ANPP
  // packet
  assert(sizeof(*_data) == _SATINFO_LEN);

  // Set _dataPtr to the address of our local _data struct
  _dataPtr = reinterpret_cast<uint8_t*>(&_data);

  // Initialize from the raw data
  _initializeFromRaw(raw, length);

  // Validate the packet data length
  // The data length must be a multiple of 7 bytes (the number of data bytes
  // per satellite)
  if ((packetDataLen() % _SATINFO_LEN) != 0) {
      std::ostringstream oss;
      oss << "Packet data length " << packetDataLen() <<
             " is invalid for DetailedSatellitesPacket";
      throw BadHeader(oss.str());
  }

  // The packet data length in the header determines how many satellites
  // we have info for
  _nSatellites = packetDataLen() / _SATINFO_LEN;

  DLOG << "DetailedSatellites packet - " << _nSatellites << " satellites";
}

DetailedSatellitesPacket::~DetailedSatellitesPacket() {
}
