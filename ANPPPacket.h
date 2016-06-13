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
  
protected:
  friend class ANPPPacketFactory;

  /// @brief This constructor unpacks the ANPP header and performs some basic 
  /// packet validation.
  /// @param rawData pointer to raw ANPP packet data
  /// @param rawLength number of bytes available in rawData
  /// @param expectedId the expected packet ID
  /// @param expectedDataLen the expected length of the non-header data in
  /// the packet (or zero if the expected length is unknown)
  ANPPPacket(const void * rawData, uint rawLength, uint8_t expectedId,
             uint8_t expectedDataLen = 0);

  /// @brief Constructor which sets header values.
  /// @param packetId the packet ID
  /// @param packetDataLen the packet non-header data length
  ANPPPacket(uint8_t packetId, uint8_t packetDataLen);

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
};

#endif /* SRC_SPATIALFOG_ANPPPACKET_H_ */
