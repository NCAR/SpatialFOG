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
/// This class is virtual; only instances of its subclasses can be constructed.
///
class ANPPPacket {
public:
  virtual ~ANPPPacket();

  /// @brief Return the ANPP packet ID
  /// @return the ANPP packet ID
  int packetId() const { return(_packetId); }

  /// @brief Return the size of the associated ANPP packet, not counting the
  /// header.
  /// @return the size of the associated ANPP packet, not counting the header.
  int packetLen() const { return(_packetLen); }

  /// @brief Exception thrown if packet data passed to the constructor is bad.
  class BadPacketData : public std::exception {
  public:
    BadPacketData(std::string msg) : _what(msg) {}
    virtual const char * what() { return(_what.c_str()); }
  private:
    std::string _what;
  };

protected:
  friend class ANPPPacketFactory;

  // @brief Construct from the object from ANPP packet data, just verifying
  // LRC for the header and CRC for the data and extracting the _packetId and
  // _packetLen.
  ANPPPacket(std::vector<uint8_t> data);

  /// @brief Return the LRC (ISO 1155 Longitudinal Redundancy Check) for the
  /// given byte array.
  /// @param bytes pointer to the array of bytes to be tested
  /// @param nbytes the number of bytes in the array
  /// @return the LRC for the byte array
  static uint8_t CalculateLRC(const uint8_t * bytes, int nbytes) {
    uint8_t lrc = 0;
    for (int i = 0; i < nbytes; i++) {
      lrc += bytes[i];          // C++: overflow (if any) is truncated
    }
    lrc = (lrc ^ 0xff) + 1;     // again, overflow is truncated
    return(lrc);
  }

  /// @brief Return true iff the given 5-byte array is a valid Advanced
  /// Navigation Packet Protocol header.
  ///
  /// Advanced Navigation Packet Protocol headers are five bytes long,
  /// and the first byte of the header is the LRC calculated for the remaining
  /// four bytes. Any five bytes where the first byte is the LRC of the next
  /// four bytes is a valid ANPP header.
  /// @param bytes pointer to the array containing the bytes to be tested. This
  /// array *must* be at least 5 bytes long.
  /// @return true iff the first 5 bytes of the array form a valid packet
  /// header.
  ///
  static bool IsValidHeader(const uint8_t * bytes) {
    return(bytes[0] == CalculateLRC(bytes + 1, 4));
  }
private:
  // ANPP packet ID
  uint8_t _packetId;
  // Packet length (without header)
  uint8_t _packetLen;
};

#endif /* SRC_SPATIALFOG_ANPPPACKET_H_ */
