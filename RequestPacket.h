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
  RequestPacket(const void* raw, uint length);
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
  
  uint _nRequestedPacketIds;
};

#endif /* SRC_SPATIALFOG_ACKPACKET_H_ */
