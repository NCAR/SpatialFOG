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

  /// @brief Return true iff the "orientation filter initialized" bit is set
  /// @return true iff the "orientation filter initialized" bit is set
  bool orientationFilterInitialized() const {
      return(((_data._filterStatus >> 0) & 0x1) == 1);
  }

  /// @brief Return true iff the "navigation filter initialized" bit is set
  /// @return true iff the "navigation filter initialized" bit is set
  bool navigationFilterInitialized() const {
      return(((_data._filterStatus >> 1) & 0x1) == 1);
  }

  /// @brief Return true iff the "heading initialized" bit is set
  /// @return true iff the "heading initialized" bit is set
  bool headingInitialized() const {
      return(((_data._filterStatus >> 2) & 0x1) == 1);
  }

  /// @brief Return true iff the "UTC time initialized" bit is set
  /// @return true iff the "UTC time initialized" bit is set
  bool utcTimeInitialized() const {
      return(((_data._filterStatus >> 3) & 0x1) == 1);
  }

  /// @brief Return the numeric GNSS fix status (0-7)
  /// @return the numeric GNSS fix status (0-7)
  uint8_t gnssFixStatus() const {
      return(uint8_t((_data._filterStatus >> 4) & 0x7));
  }

  /// @brief Return a string describing the current GNSS fix state
  /// @return a string describing the current GNSS fix state
  std::string gnssFixString() const {
      static std::string stateStrings[] = {
              "None",                   // 0
              "2D",                     // 1
              "3D",                     // 2
              "SBAS",                   // 3
              "Differential",           // 4
              "Omnistar/Starfire",      // 5
              "RTK Float",              // 6
              "RTK Fixed"               // 7
      };
      return(stateStrings[gnssFixStatus()]);
  }

  /// @brief Return latitude, in deg
  /// @return latitude, in deg
  double latitude() const { return(_RadToDeg(_data._latitude)); }

  /// @brief Return longitude, in deg
  /// @return longitude, in deg
  double longitude() const { return(_RadToDeg(_data._longitude)); }

  /// @brief Return the altitude above MSL, in m
  /// @return the altitude above MSL, in m
  double altitude() const { return(_data._height); }

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

  /// @brief Return the acceleration along the body X axis, m s-2
  /// @return the acceleration along the body X axis, m s-2
  float bodyAccelerationX() const { return(_data._bodyAccelX); }

  /// @brief Return the acceleration along the body Y axis, m s-2
  /// @return the acceleration along the body Y axis, m s-2
  float bodyAccelerationY() const { return(_data._bodyAccelY); }

  /// @brief Return the acceleration along the body Z axis, m s-2
  /// @return the acceleration along the body Z axis, m s-2
  float bodyAccelerationZ() const { return(_data._bodyAccelZ); }

  /// @brief Return the roll, in degrees
  /// @return the roll, in degrees
  float roll() const { return(_RadToDeg(_data._roll)); }

  /// @brief Return the pitch, in degrees
  /// @return the pitch, in degrees
  float pitch() const { return(_RadToDeg(_data._pitch)); }

  /// @brief Return the heading, in degrees
  /// @return the heading, in degrees
  float heading() const { return(_RadToDeg(_data._heading)); }

  /// @brief Return the angular velocity about the body X axis, deg s-1
  /// @return the angular velocity about the body X axis, deg s-1
  float bodyAngVelX() const { return(_RadToDeg(_data._angularVelX)); }

  /// @brief Return the angular velocity about the body Y axis, deg s-1
  /// @return the angular velocity about the body Y axis, deg s-1
  float bodyAngVelY() const { return(_RadToDeg(_data._angularVelY)); }

  /// @brief Return the angular velocity about the body Z axis, deg s-1
  /// @return the angular velocity about the body Z axis, deg s-1
  float bodyAngVelZ() const { return(_RadToDeg(_data._angularVelZ)); }

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
