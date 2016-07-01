/*
 * ANPPPacketFactory.h
 *
 *  Created on: Jun 1, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_ANPPPACKETFACTORY_H_
#define SRC_SPATIALFOG_ANPPPACKETFACTORY_H_

#include <inttypes.h>
#include <exception>
#include <vector>
#include "ANPPPacket.h"

class ANPPPacketFactory {
public:
  virtual ~ANPPPacketFactory();
  
  /// @brief Get the singleton ANPPPacketFactory instance.
  /// @return the singleton ANPPPacketFactory instance.
  static ANPPPacketFactory & instance() {
    if (! _instancePtr) {
      _instancePtr = new ANPPPacketFactory();
    }
    return (*_instancePtr);
  }
  
  /// @brief Return a new ANPPPacket instance created from the given raw packet
  /// bytes.
  ///
  /// The caller is responsible for deleting the returned instance.
  /// @param raw pointer to raw packet bytes from which the ANPPPacket object
  /// is to be constructed.
  /// @param len the number of bytes available in raw
  /// @return a new ANPPPacket instance created from the given raw packet bytes.
  /// @throws ANPPPacket::BadPacketData
  ANPPPacket * constructANPPPacket(const uint8_t * raw, uint32_t len) const;

private:
  /// @brief Pointer to the singleton instance
  static ANPPPacketFactory * _instancePtr;
  /// @brief Private constructor.
  ANPPPacketFactory();
};

#endif /* SRC_SPATIALFOG_ANPPPACKETFACTORY_H_ */
