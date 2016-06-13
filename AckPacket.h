/*
 * AckPacket.h
 *
 *  Created on: Jun 2, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_ACKPACKET_H_
#define SRC_SPATIALFOG_ACKPACKET_H_

#include <cinttypes>
#include <string>
#include "ANPPPacket.h"

class AckPacket: public ANPPPacket {
public:
  /// @brief Construct from raw packet data bytes
  /// @param raw the raw packet bytes
  /// @param length the number of bytes available in raw
  AckPacket(const void* raw, uint length);

  virtual ~AckPacket();
  
  /// @brief Return the ID of the acknowledged packet
  /// @return the ID of the acknowleged packet
  uint8_t ackedPacketId() const { return(_data._ackedPacketId); }
  
  /// @brief Return the CRC of the acknowledged packet
  /// @return the CRC of the acknowleged packet
  uint16_t ackedPacketCRC() const { return(_data._ackedPacketCRC); }
  
  /// @brief Return a string describing the acknowlege result
  /// @return a string describing the acknowlege result
  std::string ackResultString() const { return(AckResultStrings[_data._ackResult]); }

protected:
  /// @brief Return a pointer to the non-header data portion of the packet.
  /// @return a pointer to the non-header data portion of the packet.
  virtual const uint8_t * _dataPtr() const {
    return(reinterpret_cast<const uint8_t*>(&_data));
  }

  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 0;
  
  /// @brief Packet data size for this packet type
  static const uint8_t _PACKET_DATA_LEN = 4;

private:
  // Pack our _data struct without alignment padding, so that it matches the raw
  // packet structure byte-for-byte.
  #pragma pack(push, 1)

  /// @brief Contents of the data portion of the ANPP packet
  ///
  /// This member is explicitly stored in a packed form, so that it remains
  /// byte-for-byte compatible with raw packets sent to/from the SpatialFOG
  /// (at least on a little-endian system).
  struct {
    uint8_t _ackedPacketId;
    uint16_t _ackedPacketCRC;
    uint8_t _ackResult;
  } _data;

  // Resume default struct padding
  #pragma pack(pop)

  /// @brief Array which maps acknowledge result values to descriptive
  /// strings.
  static const std::string AckResultStrings[];
};

#endif /* SRC_SPATIALFOG_ACKPACKET_H_ */
