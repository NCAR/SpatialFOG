/*
 * RawSensorsPacket.h
 *
 *  Created on: Jul 7, 2016
 *      Author: Chris Burghart
 */

#ifndef SRC_SPATIALFOG_RAWSENSORSPACKET_H_
#define SRC_SPATIALFOG_RAWSENSORSPACKET_H_

#include "AnppPacket.h"

class RawSensorsPacket: public AnppPacket {
public:
  /// @brief Construct from raw packet data bytes
  /// @param raw the raw packet bytes
  /// @param length the number of bytes available in raw
  RawSensorsPacket(const void* raw, uint length);

  virtual ~RawSensorsPacket();
protected:
  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 28;
  
  /// @brief Packet data size for this packet type
  static const uint8_t _PACKET_DATA_LEN = 48;

private:
  // Pack our _data struct without alignment padding, so that it matches the raw
  // packet structure byte-for-byte.
  #pragma pack(push, 1)

  /// @brief Contents of the data portion of the ANPP Raw Sensors Packet
  struct {
    float _accelerometerX;  // m/s^2
    float _accelerometerY;  // m/s^2
    float _accelerometerZ;  // m/s^2
    float _gyroscopeX;      // rad/s
    float _gyroscopeY;      // rad/s
    float _gyroscopeZ;      // rad/s
    float _magnetometerX;   // mGa
    float _magnetometerY;   // mGa
    float _magnetomegerZ;   // mGa
    float _imuTemp;         // deg C
    float _pressure;        // Pa
    float _pressureTemp;    // deg C
  } _data;

  // Resume default struct padding
  #pragma pack(pop)
};

#endif /* SRC_SPATIALFOG_RAWSENSORSPACKET_H_ */
