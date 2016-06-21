/*
 * NEDVelocityPacket.h
 *
 *  Created on: Jun 14, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_NEDVELOCITYPACKET_H_
#define SRC_SPATIALFOG_NEDVELOCITYPACKET_H_

#include "ANPPPacket.h"

class NEDVelocityPacket: public ANPPPacket {
public:
  /// @brief Construct from raw packet data bytes
  /// @param raw the raw packet bytes
  /// @param length the number of bytes available in raw
  NEDVelocityPacket(const void* raw, uint length);

  virtual ~NEDVelocityPacket();
protected:
  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 35;
  
  /// @brief Packet data size for this packet type
  static const uint8_t _PACKET_DATA_LEN = 12;

private:
  // Pack our _data struct without alignment padding, so that it matches the raw
  // packet structure byte-for-byte.
  #pragma pack(push, 1)

  /// @brief Contents of the data portion of the ANPP NED Velocity Packet
  struct {
    float _velocityNorth;       // m/s
    float _velocityEast;        // m/s
    float _velocityDown;        // m/s
  } _data;

  // Resume default struct padding
  #pragma pack(pop)
};

#endif /* SRC_SPATIALFOG_NEDVELOCITYPACKET_H_ */
