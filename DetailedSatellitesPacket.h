/*
 * DetailedSatellitesPacket.h
 *
 *  Created on: Sep 22, 2016
 *      Author: Chris Burghart <burghart@ucar.edu>
 */

#ifndef _DETAILEDSATELLITESPACKET_H_
#define _DETAILEDSATELLITESPACKET_H_

#include "AnppPacket.h"

class DetailedSatellitesPacket: public AnppPacket {
public:
  /// @brief Construct from raw packet data bytes
  /// @param raw the raw packet bytes
  /// @param length the number of bytes available in raw
  DetailedSatellitesPacket(const void* raw, uint length);

  virtual ~DetailedSatellitesPacket();

  /// @brief Return count of satellites being tracked
  /// @return count of satellites being tracked
  int nSatellites() const { return(_nSatellites); }

  /// @brief Return the satellite system number for this satellite
  /// @param index index of the satellite of interest
  /// @return the satellite system number for this satellite
  int systemForIndex(int index) const { return(_data[index]._satSystem); }

  /// @brief Return the name of this satellite's system, e.g. "GPS" or "GLONASS"
  /// @param index index of the satellite of interest
  /// @return the name of this satellite's system
  const std::string systemNameForIndex(int index) const {
      static const std::string sysName[] = {
              "Unknown",
              "GPS",
              "GLONASS",
              "BeiDou",
              "GALILEO",
              "SBAS",
              "QZSS",
              "Starfire",
              "Omnistar"
      };
      return(sysName[systemForIndex(index)]);
  }

  /// @brief Return the satellite number for this satellite
  /// @param index index of the satellite of interest
  /// @return the satellite number for this satellite
  int satNumForIndex(int index) const { return(_data[index]._satNum); }


  /// @brief Return the signal-to-noise ratio for the given satellite, in dB
  /// @param index index of the satellite of interest
  /// @return the signal-to-noise ratio for the given satellite, in dB
  const int snrForIndex(int index) const {
      return(int(_data[index]._snr));
  }

protected:
  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 30;
  
  /// @brief The ANPP packet contains 7 bytes of information per tracked
  /// satellite
  static const uint8_t _SATINFO_LEN = 7;

private:
  /// @brief The number of satellites is determined by dividing the length
  /// of the data portion of the packet by _SATINFO_LEN (the number of 
  /// information bytes recorded per satellite)
  uint16_t _nSatellites;
  
  // Pack our _data struct without alignment padding, so that it matches the raw
  // packet structure byte-for-byte.
  #pragma pack(push, 1)

  /// @brief Contents of the data portion of the ANPP DetailedSatellites Packet
  struct SatInfo {
    uint8_t _satSystem; // satellite system, see manual section 13.9.12.1
    uint8_t _satNum;    // satellite number (PRN)
    uint8_t _freqBits;  // satellite frequency bit mask
    uint8_t _elevation; // satellite elevation, deg
    uint16_t _azimuth;  // satellite azimuth, deg
    uint8_t _snr;       // SNR, dB

    // default initializer
    SatInfo() :
          _satSystem(0),
          _satNum(0),
          _freqBits(0),
          _elevation(0),
          _azimuth(0),
          _snr(0) {}
  };
  struct SatInfo _data[255];

  // Resume default struct padding
  #pragma pack(pop)
};

#endif /* _DETAILEDSATELLITESPACKET_H_ */
