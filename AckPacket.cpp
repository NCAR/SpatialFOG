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

AckPacket::AckPacket(const void* raw, uint length) :
  ANPPPacket(raw, length, _PACKET_ID, _PACKET_DATA_LEN) {
  // Make sure our _data struct is the correct size and copy the raw 
  assert(sizeof(_data) == _PACKET_DATA_LEN);
  // Copy the raw bytes after the header into our data struct
  memcpy(&_data, reinterpret_cast<const uint8_t *>(raw) + _HEADER_LEN, 
         _PACKET_DATA_LEN);
}

AckPacket::~AckPacket() {
}
