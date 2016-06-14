/*
 * EulerPacket.h
 *
 *  Created on: Jun 14, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_EULERPACKET_H_
#define SRC_SPATIALFOG_EULERPACKET_H_

#include "ANPPPacket.h"

class EulerPacket: public ANPPPacket {
public:
  /// @brief Construct from raw packet data bytes
  /// @param raw the raw packet bytes
  /// @param length the number of bytes available in raw
  EulerPacket(const void* raw, uint length);

  virtual ~EulerPacket();
protected:
  /// @brief Return a pointer to the non-header data portion of the packet.
  /// @return a pointer to the non-header data portion of the packet.
  virtual const uint8_t * _dataPtr() const {
    return(reinterpret_cast<const uint8_t*>(&_data));
  }

  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 39;
  
  /// @brief Packet data size for this packet type
  static const uint8_t _PACKET_DATA_LEN = 12;

private:
  // Pack our _data struct without alignment padding, so that it matches the raw
  // packet structure byte-for-byte.
  #pragma pack(push, 1)

  /// @brief Contents of the data portion of the ANPP Euler Orientation 
  /// Standard Deviation Packet
  struct {
    float _roll;      // m
    float _pitch;     // m
    float _heading;   // m
  } _data;

  // Resume default struct padding
  #pragma pack(pop)
};

#endif /* SRC_SPATIALFOG_EULERPACKET_H_ */
