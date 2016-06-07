/*
 * RequestPacket.h
 *
 *  Created on: Jun 2, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_ACKPACKET_H_
#define SRC_SPATIALFOG_ACKPACKET_H_

#include <cinttypes>
#include <string>
//#include <boost/serialization/serialization.hpp>
#include "ANPPPacket.h"

class RequestPacket: public ANPPPacket {
public:
  /// @brief Instantiate from raw ANPP packet data.
  /// @param raw pointer to the raw packet data
  /// @param length the number of bytes of data in raw
  RequestPacket(const void* raw, uint length);
  
  /// @brief Instantiate from a list of packet IDs to be requested.
  /// @param idList a vector listing the packet IDs to be requested
  RequestPacket(const std::vector<uint8_t> idList);
  
  virtual ~RequestPacket();
  
  /// @brief Return the count of requested packet IDs.
  /// @return the count of requested packet IDs.
  uint nRequestedPacketIds() const { return(_nRequestedPacketIds); }
  
  /// @brief ANPP packet id for this packet type
  static const uint8_t PACKET_ID = 1;
  
protected:
  /// @brief Return a pointer to the non-header data portion of the packet.
  /// @return a pointer to the non-header data portion of the packet.
  virtual const uint8_t * _dataPtr() const { return(_requestedPacketIds); }

private:
  /// @brief Contents of the data portion of the ANPP packet, which is just
  /// a list of requested packet IDs.
  uint8_t _requestedPacketIds[255];
  
  uint8_t _nRequestedPacketIds;
};

#endif /* SRC_SPATIALFOG_ACKPACKET_H_ */
