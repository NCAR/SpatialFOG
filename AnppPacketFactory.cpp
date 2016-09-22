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

LOGGING("AnppPacketFactory")

// Pointer to our singleton instance, which is instantiated at first use.
AnppPacketFactory * AnppPacketFactory::_instancePtr = 0;

AnppPacketFactory::AnppPacketFactory() {
}

AnppPacketFactory::~AnppPacketFactory() {
}

AnppPacket*
AnppPacketFactory::ConstructAnppPacket(const uint8_t * raw, uint len) {
    return(instance()._constructAnppPacket(raw, len));
}

AnppPacket*
AnppPacketFactory::_constructAnppPacket(const uint8_t * raw, uint len) const {
  // Construct a non-specialized AnppPacket first, just to get access to the
  // packet ID.
  AnppPacket * pkt = new GenericPacket(raw, len);
  int packetId = pkt->packetId();
  delete pkt;
  pkt = NULL;

  // Construct the appropriate specialized packet class based on the packet ID
  switch(packetId) {
    // Acknowledge packet data -> AckPacket instance
    case 0:
      pkt = new AckPacket(raw, len);
      DLOG << "Constructed an AckPacket";
      break;
    // System State packet data -> SystemStatePacket instance
    case 20:
      pkt = new SystemStatePacket(raw, len);
      DLOG << "Constructed a SystemStatePacket";
      break;
    // Unix Time packet data -> UnixTimePacket instance
    case 21:
      pkt = new UnixTimePacket(raw, len);
      DLOG << "Constructed a UnixTimePacket";
      break;
    // Velocity Standard Deviation packet data -> VelocityStdDevPacket instance
    case 25:
      pkt = new VelocityStdDevPacket(raw, len);
      DLOG << "Constructed a VelocityStdDevPacket";
      break;
    // Euler Orientation Standard Deviation packet data -> EulerStdDevPacket
    // instance
    case 26:
      pkt = new EulerStdDevPacket(raw, len);
      DLOG << "Constructed an EulerStdDevPacket";
      break;
    // Raw Sensors packet data -> RawSensorsPacket instance
    case 28:
      pkt = new RawSensorsPacket(raw, len);
      DLOG << "Constructed a RawSensorsPacket";
      break;
    // Satellites packet data -> SatellitesPacket instance
    case 30:
      pkt = new SatellitesPacket(raw, len);
      DLOG << "Constructed a SatellitesPacket";
      break;
    // NED Velocity packet data -> NEDVelocityPacket instance
    case 35:
      pkt = new NEDVelocityPacket(raw, len);
      DLOG << "Constructed a NEDVelocityPacket";
      break;
    // Euler Orientation packet data -> EulerPacket instance
    case 39:
      pkt = new EulerPacket(raw, len);
      DLOG << "Constructed an EulerPacket";
      break;
    // For other IDs, create an unspecialized instance
    default:
      pkt = new GenericPacket(raw, len);
      DLOG << "Constructed a GenericPacket (id " << packetId << ")";
      break;
  }

  if (! pkt->crcIsGood()) {
      WLOG << "AnppPacket with id " << pkt->packetId() <<
              ": CRC in header (0x" << std::hex << pkt->crcFromHeader() <<
              ") != CRC of data (0x" << std::hex << pkt->crcOfData() << ")";
  }
  return pkt;
}
