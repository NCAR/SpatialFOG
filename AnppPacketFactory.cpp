/*
 * ANPPPacketFactory.cpp
 *
 *  Created on: Jun 1, 2016
 *      Author: burghart
 */

#include <iomanip>
#include <sstream>
#include <logx/Logging.h>
#include "AnppPacketFactory.h"
#include "AckPacket.h"
#include "EulerPacket.h"
#include "EulerStdDevPacket.h"
#include "GenericPacket.h"
#include "NEDVelocityPacket.h"
#include "RawSensorsPacket.h"
#include "SatellitesPacket.h"
#include "SystemStatePacket.h"
#include "UnixTimePacket.h"
#include "VelocityStdDevPacket.h"

LOGGING("AnppPacketFactory")

// Pointer to our singleton instance, which is instantiated at first use.
AnppPacketFactory * AnppPacketFactory::_instancePtr = 0;

AnppPacketFactory::AnppPacketFactory() {
}

AnppPacketFactory::~AnppPacketFactory() {
}

AnppPacket*
AnppPacketFactory::constructAnppPacket(const uint8_t * raw, uint len) const {
  // Construct a non-specialized AnppPacket first, just to get access to the
  // packet ID.
  GenericPacket * gPacket = new GenericPacket(raw, len);
  int packetId = gPacket->packetId();
  delete gPacket;

  // Construct the appropriate specialized packet class based on the packet ID
  switch(packetId) {
    // Acknowledge packet data -> AckPacket instance
    case 0:
      DLOG << "Constructing an AckPacket";
      return new AckPacket(raw, len);
    // System State packet data -> SystemStatePacket instance
    case 20:
      DLOG << "Constructing a SystemStatePacket";
      return new SystemStatePacket(raw, len);
    // Unix Time packet data -> UnixTimePacket instance
    case 21:
      DLOG << "Constructing a UnixTimePacket";
      return new UnixTimePacket(raw, len);
    // Velocity Standard Deviation packet data -> VelocityStdDevPacket instance
    case 25:
      DLOG << "Constructing a VelocityStdDevPacket";
      return new VelocityStdDevPacket(raw, len);
    // Euler Orientation Standard Deviation packet data -> EulerStdDevPacket
    // instance
    case 26:
      DLOG << "Constructing an EulerStdDevPacket";
      return new EulerStdDevPacket(raw, len);
    // Raw Sensors packet data -> RawSensorsPacket instance
    case 28:
      DLOG << "Constructing a RawSensorsPacket";
      return new RawSensorsPacket(raw, len);
    // Satellites packet data -> SatellitesPacket instance
    case 30:
      DLOG << "Constructing a SatellitesPacket";
      return new SatellitesPacket(raw, len);
    // NED Velocity packet data -> NEDVelocityPacket instance
    case 35:
      DLOG << "Constructing a NEDVelocityPacket";
      return new NEDVelocityPacket(raw, len);
    // Euler Orientation packet data -> EulerPacket instance
    case 39:
      DLOG << "Constructing an EulerPacket";
      return new EulerPacket(raw, len);
    // For other IDs, create an unspecialized instance
    default:
      DLOG << "Constructing a GenericPacket (id " << packetId << ")";
      return new GenericPacket(raw, len);
  }
}
