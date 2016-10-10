/*
 * DeviceInformationPacket.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: burghart
 */

#include <cassert>
#include <cmath>
#include <cstring>
#include <logx/Logging.h>
#include "DeviceInformationPacket.h"

LOGGING("DeviceInformationPacket")

DeviceInformationPacket::DeviceInformationPacket(const void* raw, uint length) {
  // Make sure our struct packs to the expected size to match the raw ANPP
  // packet
  assert(sizeof(_data) == _PACKET_DATA_LEN);

  // Set _dataPtr to the address of our local _data struct
  _dataPtr = reinterpret_cast<uint8_t*>(&_data);

  // Initialize from the raw data
  _initializeFromRaw(raw, length);

  // Validate the packet data length
  if (packetDataLen() != _PACKET_DATA_LEN) {
      std::ostringstream oss;
      oss << "Packet data length " << packetDataLen() <<
             " is invalid for DeviceInformationPacket";
      throw BadHeader(oss.str());
  }

  DLOG << "DeviceInformation packet - s/w version: " << softwareVersion() <<
          ", hardware rev: " << hardwareRevision();
}

DeviceInformationPacket::~DeviceInformationPacket() {
}

std::string
DeviceInformationPacket::deviceName() const {
    // Map from device ID number to device name. We know empirically that
    // device ID 4 is for "Spatial FOG". Others can be added when the mappings
    // are known.
    switch (deviceId()) {
    case 4:
        return("Spatial FOG");
    default:
        std::ostringstream oss;
        oss << "device id " << deviceId();
        return(oss.str());
    }
}
