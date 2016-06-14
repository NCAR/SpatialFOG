/*
 * SystemStatePacket.h
 *
 *  Created on: Jun 13, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_SYSTEMSTATEPACKET_H_
#define SRC_SPATIALFOG_SYSTEMSTATEPACKET_H_

#include "ANPPPacket.h"

class SystemStatePacket: public ANPPPacket {
public:
  /// @brief Construct from raw packet data bytes
  /// @param raw the raw packet bytes
  /// @param length the number of bytes available in raw
  SystemStatePacket(const void* raw, uint length);

  virtual ~SystemStatePacket();
  
protected:
  /// @brief Return a pointer to the non-header data portion of the packet.
  /// @return a pointer to the non-header data portion of the packet.
  virtual const uint8_t * _dataPtr() const {
    return(reinterpret_cast<const uint8_t*>(&_data));
  }

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
