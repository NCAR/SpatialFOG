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

  /// @brief Return the acceleration along the sensor X axis, m s-2
  /// @return the acceleration along the sensor X axis, m s-2
  float accelerometerX() const { return(_data._accelerometerX); }

  /// @brief Return the acceleration along the sensor Y axis, m s-2
  /// @return the acceleration along the sensor Y axis, m s-2
  float accelerometerY() const { return(_data._accelerometerY); }

  /// @brief Return the acceleration along the sensor Z axis, m s-2
  /// @return the acceleration along the sensor Z axis, m s-2
  float accelerometerZ() const { return(_data._accelerometerZ); }

  /// @brief Return the rotation rate around the sensor X axis, rad s-1
  /// @return the rotation rate around the sensor X axis, rad s-1
  float gyroscopeX() const { return(_data._gyroscopeX); }

  /// @brief Return the rotation rate around the sensor Y axis, rad s-1
  /// @return the rotation rate around the sensor Y axis, rad s-1
  float gyroscopeY() const { return(_data._gyroscopeY); }

  /// @brief Return the rotation rate around the sensor Z axis, rad s-1
  /// @return the rotation rate around the sensor Z axis, rad s-1
  float gyroscopeZ() const { return(_data._gyroscopeZ); }

  /// @brief Return the magnetic field along the sensor X axis, mG
  /// @return the magnetic field along th sensor X axis, mG
  float magnetometerX() const { return(_data._magnetometerX); }

  /// @brief Return the magnetic field along the sensor Y axis, mG
  /// @return the magnetic field along th sensor Y axis, mG
  float magnetometerY() const { return(_data._magnetometerY); }

  /// @brief Return the magnetic field along the sensor Z axis, mG
  /// @return the magnetic field along th sensor Z axis, mG
  float magnetometerZ() const { return(_data._magnetometerZ); }

  /// @brief Return the IMU temperature, deg C
  /// @return the IMU temperature, deg C
  float imuTemperature() const { return(_data._imuTemp); }

  /// @brief Return the atmospheric pressure, Pa
  /// @return the atmospheric pressure, Pa
  float pressure() const { return (_data._pressure); }

  /// @brief Return the pressure temperature (what is this?), deg C
  /// @return the pressure temperature (what is this?), deg C
  float pressureTemperature() const { return(_data._pressureTemp); }

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
    float _magnetometerZ;   // mGa
    float _imuTemp;         // deg C
    float _pressure;        // Pa
    float _pressureTemp;    // deg C
  } _data;

  // Resume default struct padding
  #pragma pack(pop)
};

#endif /* SRC_SPATIALFOG_RAWSENSORSPACKET_H_ */
