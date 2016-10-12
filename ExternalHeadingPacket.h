/*
 * ExternalHeadingPacket.h
 *
 *  Created on: Oct 12, 2016
 *      Author: Chris Burghart <burghart@ucar.edu>
 */

#ifndef SRC_SPATIALFOG_EXTERNALHEADINGPACKET_H_
#define SRC_SPATIALFOG_EXTERNALHEADINGPACKET_H_

#include <string>

#include "AnppPacket.h"

class ExternalHeadingPacket: public AnppPacket {
public:
  /// @brief Construct from raw packet data bytes
  /// @param raw the raw packet bytes
  /// @param length the number of bytes available in raw
  ExternalHeadingPacket(const void* raw, uint length);

  /// @brief Construct with a single packet ID to be requested.
  /// @param headingDev the external heading value, in degrees
  /// @param headingStdDevDeg the standard deviation of the heading, in
  /// degrees
  ExternalHeadingPacket(float headingDeg, float headingStdDevDeg);

  virtual ~ExternalHeadingPacket();
  
  /// @brief Return the external heading, deg
  /// @return the external heading, deg
  float heading() const { return(_RadToDeg(_data._heading)); }
  
  /// @brief Return the external heading standard deviation, deg
  /// @return the external heading standard deviation, deg
  float headingStdDev() const { return(_RadToDeg(_data._headingStdDev)); }
  
protected:
  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 48;
  
  /// @brief Packet data size for this packet type
  static const uint8_t _PACKET_DATA_LEN = 8;

private:
  // Pack our _data struct without alignment padding, so that it matches the raw
  // packet structure byte-for-byte.
  #pragma pack(push, 1)

  /// @brief Contents of the data portion of the ANPP External Heading Packet
  struct {
    float _heading;             // rad
    float _headingStdDev;       // rad
  } _data;

  // Resume default struct padding
  #pragma pack(pop)
};

#endif /* SRC_SPATIALFOG_EXTERNALHEADINGPACKET_H_ */
