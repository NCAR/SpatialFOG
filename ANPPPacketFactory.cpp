/*
 * ANPPPacketFactory.cpp
 *
 *  Created on: Jun 1, 2016
 *      Author: burghart
 */

#include <iomanip>
#include <sstream>
#include <logx/Logging.h>
#include "AckPacket.h"
#include "EulerPacket.h"
#include "EulerStdDevPacket.h"
#include "GenericPacket.h"
#include "NEDVelocityPacket.h"
#include "SatellitesPacket.h"
#include "SystemStatePacket.h"
#include "UnixTimePacket.h"
#include "VelocityStdDevPacket.h"
#include "ANPPPacketFactory.h"

LOGGING("ANPPPacketFactory")

// Pointer to our singleton instance, which is instantiated at first use.
ANPPPacketFactory * ANPPPacketFactory::_instancePtr = 0;

ANPPPacketFactory::ANPPPacketFactory() {
}

ANPPPacketFactory::~ANPPPacketFactory() {
}

ANPPPacket*
ANPPPacketFactory::constructANPPPacket(const uint8_t * raw, uint len) const {
  // Construct a non-specialized ANPPPacket first, just to get access to the
  // packet ID.
  GenericPacket * gPacket = new GenericPacket(raw, len);

  std::ostringstream oss;
  for (int i = 0; i < 13; i++) {
      oss << std::setw(2) << std::setfill('0') << std::hex << uint(raw[i]) << " ";
      if (i == 4) {
          oss << "  ";
      }
  }
  ILOG << "Raw header + data: " << oss.str();
  ILOG << "Created generic packet with id " << gPacket->packetId() <<
          " and data length " << gPacket->packetDataLen();

  oss.flush();
  for (int i = 0; i < 8; i++) {
      oss << std::setw(2) << std::setfill('0') << std::hex << uint(gPacket->_dataPtr[i]) << " ";
  }
  ILOG << "Constructed packet data: " << oss.str();

  delete gPacket;

  int packetId = gPacket->packetId();

  // Construct the appropriate specialized packet class based on the packet ID
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
    // For other IDs, create an unspecialized instance
    default:
      WLOG << "Creating a generic ANPPPacket for unhandled packet ID " <<
          uint(packetId);
      try {
          return new GenericPacket(raw, len);
      } catch (std::exception & ex) {
          ELOG << "2nd GenericPacket failed!";
          exit(1);
      }
  }
}
