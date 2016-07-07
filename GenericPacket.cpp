/*
 * GenericPacket.cpp
 *
 *  Created on: Jul 6, 2016
 *      Author: burghart
 */

#include <cstring>
#include <sstream>
#include <logx/Logging.h>
#include "GenericPacket.h"

LOGGING("GenericPacket")

GenericPacket::GenericPacket(const void* raw, uint length) {
    // Unpack the header and set data validity time
    _initializeHeaderFromRaw(raw, length);

    if (length < fullPacketLen()) {
        std::ostringstream oss;
        oss << "Need " << fullPacketLen() - length << " more bytes to construct";
        throw NeedMoreData(oss.str());
    }
    // Copy the raw bytes after the header into our data struct
    memcpy(&_data, reinterpret_cast<const uint8_t *>(raw) + _HEADER_LEN,
           packetDataLen());

    // Set the data pointer
    _dataPtr = reinterpret_cast<uint8_t*>(_data);
}

GenericPacket::~GenericPacket() {
}

