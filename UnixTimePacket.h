/*
 * UnixTimePacket.h
 *
 *  Created on: Jun 14, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_UNIXTIMEPACKET_H_
#define SRC_SPATIALFOG_UNIXTIMEPACKET_H_

#include "ANPPPacket.h"

class UnixTimePacket: public ANPPPacket {
public:
  /// @brief Instantiate from raw ANPP packet data.
  /// @param raw pointer to the raw packet data
  /// @param length the number of bytes of data in raw
  UnixTimePacket(const void* raw, uint length);

  virtual ~UnixTimePacket();

protected:
  /// @brief Return a pointer to the non-header data portion of the packet.
  /// @return a pointer to the non-header data portion of the packet.
  virtual const uint8_t * _dataPtr() const {
    return(reinterpret_cast<const uint8_t*>(&_data));
  }

  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 21;

  /// @brief Packet data size for this packet type
  static const uint _PACKET_DATA_LEN = 8;

private:
  // Pack our _data struct without alignment padding, so that it matches the raw
  // packet structure byte-for-byte.
  #pragma pack(push, 1)

  /// @brief Contents of the data portion of the ANPP Unix Time Packet
  struct {
    uint32_t _unixTimeSeconds;
    uint32_t _microseconds;
  } _data;

  // Resume default struct padding
  #pragma pack(pop)
};

#endif /* SRC_SPATIALFOG_UNIXTIMEPACKET_H_ */
