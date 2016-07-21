/*
 * EulerPacket.h
 *
 *  Created on: Jun 14, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_EULERPACKET_H_
#define SRC_SPATIALFOG_EULERPACKET_H_

#include "AnppPacket.h"

class EulerPacket: public AnppPacket {
public:
  /// @brief Construct from raw packet data bytes
  /// @param raw the raw packet bytes
  /// @param length the number of bytes available in raw
  EulerPacket(const void* raw, uint length);

  virtual ~EulerPacket();

  /// @brief Return the roll, in degrees
  /// @return the roll, in degrees
  float roll() const { return(_data._roll); }

  /// @brief Return the pitch, in degrees
  /// @return the pitch, in degrees
  float pitch() const { return(_data._pitch); }

  /// @brief Return the heading, in degrees
  /// @return the heading, in degrees
  float heading() const { return(_data._heading); }

protected:
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
    float _roll;      // rad
    float _pitch;     // rad
    float _heading;   // rad
  } _data;

  // Resume default struct padding
  #pragma pack(pop)
};

#endif /* SRC_SPATIALFOG_EULERPACKET_H_ */
