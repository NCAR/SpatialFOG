/*
 * AckPacket.cpp
 *
 *  Created on: Jun 2, 2016
 *      Author: burghart
 */

#include <cassert>
#include <cstring>
#include <sstream>
#include <logx/Logging.h>
#include "AckPacket.h"

LOGGING("AckPacket")

// Map integer ack results to descriptive strings
const std::string AckPacket::AckResultStrings[] = {
    "success",
    "CRC error",
    "packet size incorrect",
    "values outside of valid ranges",
    "system flash memory failure",
    "system not ready",
    "unknown packet"
};

AckPacket::AckPacket(const void* raw, uint length) {
  // Make sure our struct packs to the expected size to match the raw ANPP
  // packet
  assert(sizeof(_data) == _PACKET_DATA_LEN);

  // Set _dataPtr to the address of our local _data struct
  _dataPtr = reinterpret_cast<uint8_t*>(&_data);
  // Initialize from the raw data
  _initializeFromRaw(raw, length);

  DLOG << "Acknowledgment packet - For pkt ID " << uint(ackedPacketId()) <<
          ": " << ackResultString();
}

AckPacket::~AckPacket() {
}
