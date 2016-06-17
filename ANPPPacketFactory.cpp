/*
 * ANPPPacketFactory.cpp
 *
 *  Created on: Jun 1, 2016
 *      Author: burghart
 */

#include <sstream>
#include "AckPacket.h"
#include "EulerPacket.h"
#include "EulerStdDevPacket.h"
#include "NEDVelocityPacket.h"
#include "SatellitesPacket.h"
#include "SystemStatePacket.h"
#include "UnixTimePacket.h"
#include "VelocityStdDevPacket.h"
#include "ANPPPacketFactory.h"

// Pointer to our singleton instance, which is instantiated at first use.
ANPPPacketFactory * ANPPPacketFactory::_instancePtr = 0;

ANPPPacketFactory::ANPPPacketFactory() {
}

ANPPPacketFactory::~ANPPPacketFactory() {
}

ANPPPacket*
ANPPPacketFactory::constructANPPPacket(const uint8_t * raw, uint len) const {
  // Make sure we got at least 5 bytes and test that the first 5 bytes are
  // a good ANPP header.
  if (len < 5 || ! ANPPPacket::IsValidHeader(raw)) {
    throw(ANPPPacket::BadPacketData("Raw data does not contain a good ANPP packet header"));
  }

  // Extract the packet ID from the ANPP header
  uint8_t packetId = raw[1];

  // Call the appropriate constructor based on the packet ID
  switch(packetId) {
    // Acknowledge packet data -> AckPacket instance
    case 0:
      return new AckPacket(raw, len);
    // System State packet data -> SystemStatePacket instance
    case 20:
      return new SystemStatePacket(raw, len);
    // Unix Time packet data -> UnixTimePacket instance
    case 21:
      return new UnixTimePacket(raw, len);
    // Velocity Standard Deviation packet data -> VelocityStdDevPacket instance
    case 25:
      return new VelocityStdDevPacket(raw, len);
    // Euler Orientation Standard Deviation packet data -> VelocityStdDevPacket
    // instance
    case 26:
      return new EulerStdDevPacket(raw, len);
    // Satellites packet data -> VelocityStdDevPacket instance
    case 30:
      return new SatellitesPacket(raw, len);
    // NED Velocity packet data -> NEDVelocityPacket instance
    case 35:
      return new NEDVelocityPacket(raw, len);
    // Euler Orientation packet data -> EulerPacket instance
    case 39:
      return new EulerPacket(raw, len);
    // For other IDs, we don't have a class to match the packet id, so bail out
    default:
      std::ostringstream oss;
      oss << "No ANPPPacket subclass for packet id " << uint(packetId);
      throw(ANPPPacket::BadPacketData(oss.str()));
  }
}
