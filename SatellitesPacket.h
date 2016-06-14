/*
 * SatellitesPacket.h
 *
 *  Created on: Jun 14, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_SATELLITESPACKET_H_
#define SRC_SPATIALFOG_SATELLITESPACKET_H_

#include "ANPPPacket.h"

class SatellitesPacket: public ANPPPacket {
public:
  /// @brief Construct from raw packet data bytes
  /// @param raw the raw packet bytes
  /// @param length the number of bytes available in raw
  SatellitesPacket(const void* raw, uint length);

  virtual ~SatellitesPacket();
protected:
  /// @brief Return a pointer to the non-header data portion of the packet.
  /// @return a pointer to the non-header data portion of the packet.
  virtual const uint8_t * _dataPtr() const {
    return(reinterpret_cast<const uint8_t*>(&_data));
  }

  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 30;
  
  /// @brief Packet data size for this packet type
  static const uint8_t _PACKET_DATA_LEN = 13;

private:
  // Pack our _data struct without alignment padding, so that it matches the raw
  // packet structure byte-for-byte.
  #pragma pack(push, 1)

  /// @brief Contents of the data portion of the ANPP Satellites Packet
  struct {
    float _hdop;        // horizontal dilution of precision
    float _vdop;        // vertical dilution of precision
    uint8_t _nGps;      // # of GPS satellites
    uint8_t _nGlonass;  // # of GLONASS satellites
    uint8_t _nBeiDou;   // # of BeiDou satellites
    uint8_t _nGalileo;  // # of Galileo satellites
    uint8_t _nSBAS;     // # of SBAS satellites
  } _data;

  // Resume default struct padding
  #pragma pack(pop)
};

#endif /* SRC_SPATIALFOG_SATELLITESPACKET_H_ */
