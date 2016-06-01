/*
 * ANPPPacket.cpp
 *
 *  Created on: Jun 1, 2016
 *      Author: burghart
 */

#include <cstdlib>
#include <cstring>
#include <logx/Logging.h>
#include "ANPPPacket.h"

LOGGING("ANPPPacket");

ANPPPacket::ANPPPacket(std::vector<uint8_t> data) {
  // We must have at least 5 bytes (the header length)
  if (data.size() < 5) {
    throw BadPacketData("Packet data too short for valid ANPP packet");
  }
  
  // Check the header to see if the LRC matches the contents
  if (! IsValidHeader(data.data())) {
    throw BadPacketData("Header LRC does not match header contents");
  }
  
  // Extract the packet ID, length, and CRC from the header
  _packetId = data[1];
  _packetLen = data[2];

  // ANPP packets contain little-endian data, and we tacitly assume when
  // we're packing/unpacking them that the machine we're working on is also 
  // little-endian. Verify that now.
  union {
    uint32_t i;
    char c[4];
  } endianTest = 0x01020304;
  bool littleEndian = (endianTest.c[0] == 0x04);
  if (! littleEndian) {
    ELOG << ANPPPacket implementation only works on little-endian machines!";
    exit(1);
  }
  
  // Extract bytes 3 and 4 from the header. (Here's the first of many places
  // where we require that machine representation is little-endian.)
  uint16_t crc;
  memcpy(&crc, data.data() + 3, 2);
}

ANPPPacket::~ANPPPacket() {
}

uint16_t
ANPPPacket::CalculateCRC(const uint8_t * bytes, int nbytes) {
  static const uint16_t POLYNOMIAL = 0x1021;
  static const uint16_t INITIAL_VALUE = 0xffff;

  uint16_t crc = INITIAL_VALUE;
  
  for (int byte = 0; byte < nbytes; byte++) {
    for (int bit = 0; bit < 8; bit++) {
      bool xor_flag = ((crc & 0x8000) != 0);
      uint16_t v = 0x1 << (7 - bit); // Set the test bit
      
      crc = crc << 1;
      
      if (bytes[byte] & v) {
        // Append next bit of message to end of CRC if it is not zero.
        crc = crc + 1;
      }
      
      if (xor_flag) {
        crc = crc ^ POLYNOMIAL;
      }
    }
  }
  return crc;
}
