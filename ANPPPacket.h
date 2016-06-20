/*
 * ANPPPacket.h
 *
 *  Created on: Jun 1, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_ANPPPACKET_H_
#define SRC_SPATIALFOG_ANPPPACKET_H_

#include <cinttypes>
#include <exception>
#include <string>
#include <vector>

///
/// @brief Base class for C++ representation of Advanced Navigation Packet
/// Protocol (ANPP) packets.
///
/// There is no public constructor for this virtual base class. Only subclasses
/// can be instantiated directly.
///
class ANPPPacket {
public:
  virtual ~ANPPPacket();
  
  /// @brief Return the ANPP header LRC
  /// @return the ANPP header LRC
  int headerLRC() const { return(_header._headerLRC); }

  /// @brief Return the ANPP packet ID
  /// @return the ANPP packet ID
  int packetId() const { return(_header._packetId); }

  /// @brief Return the size of the associated ANPP packet, not counting the
  /// header.
  /// @return the size of the associated ANPP packet, not counting the header.
  int packetDataLen() const { return(_header._packetDataLen); }
  
  /// @brief Return the CRC for the data (non-header) portion of the packet.
  /// @return the CRC for the data (non-header) portion of the packet.
  uint16_t packetDataCRC() { return(_header._packetDataCRC); }
  
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

  /// @brief Exception thrown if packet data passed to the constructor is bad.
  class BadPacketData : public std::exception {
  public:
    BadPacketData(std::string msg) : _what(msg) {}
    
    virtual const char * what() { return(_what.c_str()); }
  private:
    std::string _what;
  };

  /// @brief Calculate and return the ISO 1155 Longitudinal Redundancy Check 
  /// (LRC) for a series of bytes.
  /// @param data pointer to the array of bytes to be checked
  /// @param length the number of bytes in the array to check
  /// @return the ISO 1155 Longitudinal Redundancy Check (LRC) for the bytes
  static uint8_t CalculateLRC(const void * data, int length);

  /// @brief Calculate and return the CRC16-CCITT for a series of bytes.
  /// @param data pointer to the array of bytes to be checked
  /// @param length the number of bytes in the array to check
  /// @return the CRC16-CCITT for the bytes
  static uint16_t CalculateCRC(const void * data, int length);

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
  
  /// @brief Return true iff the first 5 bytes pointed to by bytes comprise a
  /// valid ANPP packet header.
  /// @param bytes a pointer to at least 5 bytes of readable memory
  /// @return true iff the first 5 bytes pointed to by bytes comprise a valid
  /// ANPP packet header.
  static bool IsValidHeader(const uint8_t * bytes) {
    // In a valid 5-byte ANPP packet header, the first byte contains the LRC
    // for the following four bytes.
    return(bytes[0] == CalculateLRC(bytes + 1, 4));
  }

protected:
  friend class ANPPPacketFactory;

  /// @brief This constructor unpacks the ANPP header and performs some basic 
  /// packet validation.
  ///
  /// The constructor also sets the time of validity of the packet to the
  /// latest time of validity obtained from a System State or Unix Time packet.
  ///
  /// @param rawData pointer to raw ANPP packet data
  /// @param rawLength number of bytes available in rawData
  /// @param expectedId the expected packet ID
  /// @param expectedDataLen the expected length of the non-header data in
  /// the packet (or zero if the expected length is unknown)
  /// @throws BadPacketData
  ANPPPacket(const void * rawData, uint rawLength, uint8_t expectedId,
             uint8_t expectedDataLen = 0);

  /// @brief Constructor which sets header values.
  /// @param packetId the packet ID
  /// @param packetDataLen the packet non-header data length
  ANPPPacket(uint8_t packetId, uint8_t packetDataLen);

  /// @brief The fixed length of the ANPP packet header: 5 bytes
  static const uint _HEADER_LEN = 5;

  /// @brief Return a pointer to the non-header data portion of the packet.
  ///
  /// This must point to at least _packetLen valid bytes of memory.
  virtual const uint8_t * _dataPtr() const = 0;

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

private:
  // Contents of the header portion of the ANPP packet. We use #pragma pack(1)
  // to force storage without any alignment padding, so that this matches the 
  // ANPP header structure byte-for-byte.
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
  
  // Time of validity for the packet. This time is not sent with every packet,
  // but is taken from the last System State or Unix Time packet delivered.
  uint32_t _timeOfValiditySeconds;
  uint32_t _timeOfValidityMicroseconds;
};

#endif /* SRC_SPATIALFOG_ANPPPACKET_H_ */
