/*
 * ANPPPacket.h
 *
 *  Created on: Jun 1, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_ANPPPACKET_H_
#define SRC_SPATIALFOG_ANPPPACKET_H_

#include <stdint.h>
#include <exception>
#include <string>
#include <vector>

///
/// @brief Base class for C++ representation of Advanced Navigation Packet
/// Protocol (ANPP) packets.
///
class ANPPPacket {
public:
  ANPPPacket();
  virtual ~ANPPPacket();
  
  /// @brief Return the ANPP header LRC
  /// @return the ANPP header LRC
  int headerLRC() const { return(_header._headerLRC); }

  /// @brief Return the ANPP packet ID
  /// @return the ANPP packet ID
  int packetId() const { return(_header._packetId); }

  /// @brief Return the size in bytes of the raw ANPP packet, not counting the
  /// header.
  /// @return the size of the associated ANPP packet, not counting the header.
  uint32_t packetDataLen() const { return(_header._packetDataLen); }
  
  /// @brief Return the size in bytes of the raw ANPP packet, including the
  /// header.
  /// @return the size in bytes of the raw ANPP packet, including the header.
  uint32_t fullPacketLen() const { return(_HEADER_LEN + packetDataLen()); }

  /// @brief Return the CRC for the data (non-header) portion of the packet,
  /// as recorded in the packet header.
  /// @return the CRC for the data (non-header) portion of the packet, as
  /// recorded in the packet header.
  uint16_t crcFromHeader() { return(_header._packetDataCRC); }
  
  /// @brief Return the time of validity for the packet, in whole seconds since
  /// 1970-01-01 00:00:00 UTC.
  /// @return the time of validity for the packet, in whole seconds since
  /// 1970-01-01 00:00:00 UTC.
  uint32_t timeOfValiditySeconds() { return(_timeOfValiditySeconds); }
  
  /// @brief Return the subsecond portion of time of validity for the packet,
  /// in microseconds.
  /// @return the subsecond portion of time of validity for the packet,
  /// in microseconds.
  uint32_t timeOfValidityMicroseconds() { return(_timeOfValidityMicroseconds); }
  
  /// @brief Return the value of timeOfValiditySeconds() + 
  /// 1.0e-6 * timeOfValidityMicroseconds(), expressed as a double-precision
  /// float.
  /// @return Return the value of timeOfValiditySeconds() + 
  /// 1.0e-6 * timeOfValidityMicroseconds(), expressed as a double-precision
  /// float.
  double timeOfValidity() { 
    return(timeOfValiditySeconds() + 1.0e-6 * timeOfValidityMicroseconds());
  }

  /// @brief Return true iff the CRC recorded in the header matches the CRC
  /// calculated for the data portion of the packet.
  bool crcIsGood();

  /// @brief Exception thrown if the LRC in the header does not match the
  /// LRC calculated from the header contents, or if the header is all zeros.
  class BadHeader : public std::exception {
  public:
	  BadHeader(std::string msg) : _what(msg) {}
	  virtual ~BadHeader() throw ();
	  virtual const char * what() { return(_what.c_str()); }
  private:
	  std::string _what;
  };

  /// @brief Exception thrown if the number of bytes passed to the constructor
  /// is not enough to construct a complete packet.
  ///
  /// The number of bytes passed to the constructor must be at least 5
  /// (the size of the header) + the number of packet data bytes given in the
  /// header (up to 255).
  class NeedMoreData : public std::exception {
  public:
	  NeedMoreData(std::string msg) : _what(msg) {}
	  virtual ~NeedMoreData() throw ();
	  virtual const char * what() { return(_what.c_str()); }
  private:
	  std::string _what;
  };

  /// @brief Return true iff the machine is little-endian.
  /// @return true iff the machine is little-endian.
  static bool MachineIsLittleEndian() {
    union {
      uint32_t i;
      char c[4];
    } endianTest;
    endianTest.i = 0x01020304;
    return(endianTest.c[0] == 0x04);
  }
  
protected:
  friend class ANPPPacketFactory;

  /// @brief This method unpacks the 5-byte ANPP header, sets the time of
  /// validity for the packet, and performs header validation.
  /// @param rawData pointer to raw ANPP packet data
  /// @param rawLength number of bytes available in rawData
  /// @throw NeedMoreData if rawLength is less than 5 bytes.
  /// @throw BadHeaderLRC if the LRC recorded in the header does not match
  /// the LRC computed from the header contents.
  void _initializeHeaderFromRaw(const void * rawData, uint32_t rawLength);

  /// @brief Constructor which sets header values.
  /// @param packetId the packet ID
  /// @param packetDataLen the packet non-header data length
  ANPPPacket(uint8_t packetId, uint8_t packetDataLen);

  /// @brief The fixed length of the ANPP packet header: 5 bytes
  static const uint8_t _HEADER_LEN = 5;

  /// @brief Recalculate the LRC and CRC in the header to reflect all of the
  /// other values in the packet.
  ///
  /// This should be called whenever changes are made to the packet ID, 
  /// packet data length, or the packet data contents.
  void _updateHeader();

  /// @brief Set the object's time of validity, in seconds and microseconds
  /// since 1970-01-01 00:00:00 UTC.
  void _setTimeOfValidity(uint32_t unixSeconds,
                          uint32_t microseconds) {
    _timeOfValiditySeconds = unixSeconds;
    _timeOfValidityMicroseconds = microseconds;
  }

  /// @brief Set the object's time of validity to the latest time of validity
  /// received from the Spatial FOG
  void _setTimeOfValidity() {
    _timeOfValiditySeconds = _LatestTimeOfValiditySeconds;
    _timeOfValidityMicroseconds = _LatestTimeOfValidityMicroseconds;
  }

  /// @brief Store the latest time of validity received from the SpatialFOG, in
  /// Unix time format. This time is sent in both System State and Unix Time 
  /// packets, and applies to all packets delivered in the same packet sequence.
  /// (See the Spatial FOG Reference Manual, section 13.6-Packet Timing.)
  static uint32_t _LatestTimeOfValiditySeconds;
  static uint32_t _LatestTimeOfValidityMicroseconds;
  static void _SetLatestTimeOfValidity(uint32_t unixSeconds,
                                       uint32_t microseconds) {
    _LatestTimeOfValiditySeconds = unixSeconds;
    _LatestTimeOfValidityMicroseconds = microseconds;
  }

  /// @brief Pointer to memory holding the non-header data contents of the
  /// packet. The size of the memory pointed to must be at least packetDataLen()
  /// bytes.
  uint8_t * _dataPtr;

private:
  /// @brief Calculate and return the ISO 1155 Longitudinal Redundancy Check
  /// (LRC) for a series of bytes.
  /// @param data pointer to the array of bytes to be checked
  /// @param length the number of bytes in the array to check
  /// @return the ISO 1155 Longitudinal Redundancy Check (LRC) for the bytes
  static uint8_t _CalculateLRC(const void * data, int length);

  /// @brief Calculate and return the CRC16-CCITT for a series of bytes.
  /// @param data pointer to the array of bytes to be checked
  /// @param length the number of bytes in the array to check
  /// @return the CRC16-CCITT for the bytes
  static uint16_t _CalculateCRC(const void * data, int length);

  /// @brief Contents of the header portion of the ANPP packet. We use
  /// #pragma pack(1) to force storage without any alignment padding, so that
  /// this matches the ANPP header structure byte-for-byte.
  #pragma pack(push, 1) // pack struct without alignment padding
  struct {
    // Header LRC
    uint8_t _headerLRC;
    // ANPP packet ID
    uint8_t _packetId;
    // Packet data length (without header)
    uint8_t _packetDataLen;
    // Packet data CRC
    uint16_t _packetDataCRC;
  } _header;
  #pragma pack(pop)     // resume default struct padding
  
  /// @brief Time of validity for the packet.
  ///
  /// This time is not sent with every packet, but is taken from the last
  /// System State or Unix Time packet received.
  uint32_t _timeOfValiditySeconds;
  uint32_t _timeOfValidityMicroseconds;
};

#endif /* SRC_SPATIALFOG_ANPPPACKET_H_ */
