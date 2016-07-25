/*
 * SystemStatePacket.h
 *
 *  Created on: Jun 13, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_SYSTEMSTATEPACKET_H_
#define SRC_SPATIALFOG_SYSTEMSTATEPACKET_H_

#include <cmath>
#include "AnppPacket.h"

class SystemStatePacket: public AnppPacket {
public:
  /// @brief Construct from raw packet data bytes
  /// @param raw the raw packet bytes
  /// @param length the number of bytes available in raw
  SystemStatePacket(const void* raw, uint length);

  virtual ~SystemStatePacket();

  /// @brief Return system status bits. See the Advanced Navigation Packet
  /// Protocol documentation for details.
  /// @return system status bits
  uint16_t systemStatus() const { return(_data._systemStatus); }

  /// @brief Return filter status bits. See the Advanced Navigation Packet
  /// Protocol documentation for details.
  /// @return filter status bits
  uint16_t filterStatus() const { return(_data._filterStatus); }

  /// @brief Return latitude, in deg
  /// @return latitude, in deg
  float latitude() const { return(_RadToDeg(_data._latitude)); }

  /// @brief Return longitude, in deg
  /// @return longitude, in deg
  float longitude() const { return(_RadToDeg(_data._longitude)); }

  /// @brief Return the altitude above MSL, in m
  /// @return the altitude above MSL, in m
  float altitude() const { return(_data._height); }

  /// @brief Return the velocity north, in m/s
  /// @return the velocity north, in m/s
  float velocityNorth() const { return(_data._velNorth); }

  /// @brief Return the velocity east, in m/s
  /// @return the velocity east, in m/s
  float velocityEast() const { return(_data._velEast); }

  /// @brief Return the velocity down, in m/s
  /// @return the velocity down, in m/s
  float velocityDown() const { return(_data._velDown); }

  /// @brief Return the velocity up, in m/s
  /// @return the velocity up, in m/s
  float velocityUp() const { return(-1 * velocityDown()); }

  /// @brief Return the roll, in degrees
  /// @return the roll, in degrees
  float roll() const { return(_RadToDeg(_data._roll)); }

  /// @brief Return the pitch, in degrees
  /// @return the pitch, in degrees
  float pitch() const { return(_RadToDeg(_data._pitch)); }

  /// @brief Return the heading, in degrees
  /// @return the heading, in degrees
  float heading() const { return(_RadToDeg(_data._heading)); }

protected:
  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 20;
  
  /// @brief Packet data size for this packet type
  static const uint8_t _PACKET_DATA_LEN = 100;

private:
  // Pack our _data struct without alignment padding, so that it matches the raw
  // packet structure byte-for-byte.
  #pragma pack(push, 1)

  /// @brief Contents of the data portion of the ANPP System State Packet
  struct {
    uint16_t _systemStatus;     // 16 system status bits
    uint16_t _filterStatus;     // 16 filter status bits
    uint32_t _unixTimeSeconds;
    uint32_t _microseconds;
    double _latitude;           // rad
    double _longitude;          // rad
    double _height;             // m MSL
    float _velNorth;            // m/s
    float _velEast;             // m/s
    float _velDown;             // m/s
    float _bodyAccelX;          // m/s^2
    float _bodyAccelY;          // m/s^2
    float _bodyAccelZ;          // m/s^2
    float _gForce;              // g
    float _roll;                // rad
    float _pitch;               // rad
    float _heading;             // rad
    float _angularVelX;         // rad/s
    float _angularVelY;         // rad/s
    float _angularVelZ;         // rad/s
    float _latitudeStdDev;      // m
    float _longitudeStdDev;     // m
    float _heightStdDev;        // m
  } _data;

  // Resume default struct padding
  #pragma pack(pop)

  /// @brief Array which maps acknowledge result values to descriptive
  /// strings.
  static const std::string AckResultStrings[];
};

#endif /* SRC_SPATIALFOG_SYSTEMSTATEPACKET_H_ */
