/*
 * RequestPacket.h
 *
 *  Created on: Jun 2, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_REQUESTPACKET_H_
#define SRC_SPATIALFOG_REQUESTPACKET_H_

#include <cinttypes>
#include <string>
#include "ANPPPacket.h"

class RequestPacket: public ANPPPacket {
public:
  /// @brief Construct with a single packet ID to be requested.
  /// @param id the packet ID to be requested
  RequestPacket(uint8_t id);

  /// @brief Construct with a list of packet IDs to be requested.
  /// @param idList a vector listing the packet IDs to be requested
  RequestPacket(const std::vector<uint8_t> idList);
  
  virtual ~RequestPacket();
  
  /// @brief Return the count of requested packet IDs.
  /// @return the count of requested packet IDs.
  uint nRequestedPacketIds() const { return(_nRequestedPacketIds); }
  
protected:
  /// @brief ANPP packet id for this packet type
  static const uint8_t _PACKET_ID = 1;
  
private:
  /// @brief Contents of the data portion of the ANPP Request Packet, which is
  /// just a list of requested packet IDs.
  uint8_t _requestedPacketIds[255];
  
  uint8_t _nRequestedPacketIds;
};

#endif /* SRC_SPATIALFOG_REQUESTPACKET_H_ */
