/*
 * ANPPPacketFactory.h
 *
 *  Created on: Jun 1, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_ANPPPACKETFACTORY_H_
#define SRC_SPATIALFOG_ANPPPACKETFACTORY_H_

#include <vector>
#include "ANPPPacket.h"
//#include "AckPacket.h"

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
  
  ANPPPacket * createANPPPacket(const std::vector<uint8_t> & bytes);
private:
  /// @brief Pointer to the singleton instance
  static ANPPPacketFactory * _instancePtr;
  /// @brief Private constructor.
  ANPPPacketFactory();
};

#endif /* SRC_SPATIALFOG_ANPPPACKETFACTORY_H_ */
