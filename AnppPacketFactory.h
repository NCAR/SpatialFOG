/*
 * AnppPacketFactory.h
 *
 *  Created on: Jun 1, 2016
 *      Author: Chris Burghart <burghart@ucar.edu>
 */

#ifndef SRC_SPATIALFOG_ANPPPACKETFACTORY_H_
#define SRC_SPATIALFOG_ANPPPACKETFACTORY_H_

#include <inttypes.h>
#include <exception>
#include <vector>
#include "AnppPacket.h"

class AnppPacketFactory {
public:
  virtual ~AnppPacketFactory();
  
  /// @brief Get the singleton AnppPacketFactory instance.
  /// @return the singleton AnppPacketFactory instance.
  static AnppPacketFactory & instance() {
    if (! _instancePtr) {
      _instancePtr = new AnppPacketFactory();
    }
    return (*_instancePtr);
  }
  
  /// @brief Return a new AnppPacket instance created from the given raw packet
  /// bytes.
  ///
  /// The caller is responsible for deleting the returned instance.
  /// @param raw pointer to raw packet bytes from which the AnppPacket object
  /// is to be constructed.
  /// @param len the number of bytes available in raw
  /// @return a new AnppPacket instance created from the given raw packet bytes.
  /// @throws AnppPacket::BadPacketData
  AnppPacket * constructAnppPacket(const uint8_t * raw, uint32_t len) const;

private:
  /// @brief Pointer to the singleton instance
  static AnppPacketFactory * _instancePtr;
  /// @brief Private constructor.
  AnppPacketFactory();
};

#endif /* SRC_SPATIALFOG_ANPPPACKETFACTORY_H_ */
