/*
 * DeviceInformationPacket.h
 *
 *  Created on: Jun 14, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_DEVICEINFORMATIONPACKET_H_
#define SRC_SPATIALFOG_DEVICEINFORMATIONPACKET_H_

#include "AnppPacket.h"

class DeviceInformationPacket: public AnppPacket {
public:
  /// @brief Construct from raw packet data bytes
  /// @param raw the raw packet bytes
  /// @param length the number of bytes available in raw
  DeviceInformationPacket(const void* raw, uint length);

  virtual ~DeviceInformationPacket();

  /// @brief return the software version number
  /// @return the software version number
  uint32_t softwareVersion() const { return(_data._softwareVersion); }

  /// @brief return the device ID number
  /// @return the device ID number
  uint32_t deviceId() const { return(_data._deviceId); }

  /// @brief return the device name associated with the device ID number,
  /// @return the device name associated with the device ID number
  std::string deviceName() const;

  /// @brief return the hardware revision
  /// @return the hardware revision
  uint32_t hardwareRevision() const { return(_data._hardwareRevision); }

  /// @brief return the serial number part 1
  /// @return the serial number part 1
  uint32_t serialNumberPart1() const { return(_data._serialNumberPart1); }

  /// @brief return the serial number part 2
  /// @return the serial number part 2
  uint32_t serialNumberPart2() const { return(_data._serialNumberPart2); }

  /// @brief return the serial number part 3
  /// @return the serial number part 3
  uint32_t serialNumberPart3() const { return(_data._serialNumberPart3); }

protected:
  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 3;
  
  /// @brief Packet data size for this packet type
  static const uint8_t _PACKET_DATA_LEN = 24;

private:
  // Pack our _data struct without alignment padding, so that it matches the raw
  // packet structure byte-for-byte.
  #pragma pack(push, 1)

  /// @brief Contents of the data portion of the ANPP DeviceInformation Orientation 
  struct {
    uint32_t _softwareVersion;
    uint32_t _deviceId;
    uint32_t _hardwareRevision;
    uint32_t _serialNumberPart1;
    uint32_t _serialNumberPart2;
    uint32_t _serialNumberPart3;
  } _data;

  // Resume default struct padding
  #pragma pack(pop)
};

#endif /* SRC_SPATIALFOG_DEVICEINFORMATIONPACKET_H_ */
