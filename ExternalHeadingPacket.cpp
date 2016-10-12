/*
 * ExternalHeadingPacket.cpp
 *
 *  Created on: Oct 12, 2016
 *      Author: Chris Burghart <burghart@ucar.edu>
 */

#include <cstring>
#include <sstream>
#include <logx/Logging.h>
#include "ExternalHeadingPacket.h"

LOGGING("ExternalHeadingPacket")

ExternalHeadingPacket::ExternalHeadingPacket(const void* raw, uint length) {
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
             " is invalid for ExternalHeadingPacket";
      throw BadHeader(oss.str());
  }

  DLOG << "ExternalHeading packet - heading: " << heading() <<
          ", std. dev.: " << headingStdDev();
}

ExternalHeadingPacket::ExternalHeadingPacket(float headingDeg,
                                             float headingStdDevDeg) :
  AnppPacket(_PACKET_ID, _PACKET_DATA_LEN) {
  // Fill our data struct
  _data._heading = _DegToRad(headingDeg);               // convert to rad
  _data._headingStdDev = _DegToRad(headingStdDevDeg);   // convert to rad

  // Set the data pointer
  _dataPtr = reinterpret_cast<uint8_t*>(&_data);

  // Update the header LRC and CRC to reflect the new data contents
  _updateHeader();
}

ExternalHeadingPacket::~ExternalHeadingPacket() {
}
