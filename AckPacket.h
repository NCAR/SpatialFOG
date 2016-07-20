/*
 * AckPacket.h
 *
 *  Created on: Jun 2, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_ACKPACKET_H_
#define SRC_SPATIALFOG_ACKPACKET_H_

#include <cinttypes>
#include <string>

#include "AnppPacket.h"

class AckPacket: public AnppPacket {
public:
  /// @brief Construct from the data in rawData, which contains rawLength
  /// usable bytes.
  ///
  /// If the constructor is successful, the number of bytes used from raw
  /// is given by the fullPacketLen() method of the returned instance.
  ///
  /// It is recommended that the user call the crcIsGood() method to verify
  /// that the CRC contained in the packet header matches the CRC calculated
  /// for the data portion of the packet.
  ///
  /// @param rawData pointer to raw data bytes
  /// @param rawLength the number of bytes available in rawData
  ///
  /// @throw BadHeaderLRC if the LRC computed for the header contents does not
  /// match the LRC recorded at the start of the header.
  /// @throw NeedMoreData if length is less than 5 bytes (the header length)
  /// or if length is shorter than the header length + the data length written
  /// in the header
  AckPacket(const void* rawData, uint rawLength);

  virtual ~AckPacket();
  
  /// @brief Return the ID of the acknowledged packet
  /// @return the ID of the acknowleged packet
  uint8_t ackedPacketId() const { return(_data._ackedPacketId); }
  
  /// @brief Return the CRC of the acknowledged packet
  /// @return the CRC of the acknowleged packet
  uint16_t ackedPacketCRC() const { return(_data._ackedPacketCRC); }
  
  /// @brief Return a string describing the acknowlege result
  /// @return a string describing the acknowlege result
  std::string ackResultString() const { return(AckResultStrings[_data._ackResult]); }

protected:
  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 0;
  
  /// @brief Packet data size for this packet type
  static const uint8_t _PACKET_DATA_LEN = 4;

private:
  // Pack our _data struct without alignment padding, so that it matches the raw
  // packet structure byte-for-byte.
  #pragma pack(push, 1)

  /// @brief Contents of the data portion of the ANPP Acknowledge Packet
  struct {
    uint8_t _ackedPacketId;
    uint16_t _ackedPacketCRC;
    uint8_t _ackResult;
  } _data;

  // Resume default struct padding
  #pragma pack(pop)

  /// @brief Array which maps acknowledge result values to descriptive
  /// strings.
  static const std::string AckResultStrings[];
};

#endif /* SRC_SPATIALFOG_ACKPACKET_H_ */
