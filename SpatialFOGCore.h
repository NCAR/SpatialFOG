/*
 * SpatialFOGCore.h
 *
 *  Created on: May 27, 2016
 *      Author: burghart
 */

#ifndef SRC_SPATIALFOG_SPATIALFOGCORE_H_
#define SRC_SPATIALFOG_SPATIALFOGCORE_H_

/**
 * @brief SpatialFOGCore provides the business-knowledge core for configuring
 * a SpatialFOG INS unit and for interpreting its data packets.
 */
class SpatialFOGCore {
public:
  SpatialFOGCore();
  virtual ~SpatialFOGCore();
  
  /**
   * @brief Return the LRC (ISO 1155 Longitudinal Redundancy Check) for the 
   * given byte array.
   * @param bytes pointer to the array of bytes to be tested
   * @param nbytes the number of bytes in the array
   * @return the LRC for the byte array
   */
  static uint8_t CalculateLRC(const uint8_t * bytes, int nbytes) {
    uint8_t lrc = 0;
    for (int i = 0; i < nbytes; i++) {
      lrc += bytes[i];  // C++: overflow (if any) is truncated
    }
    lrc = (lrc ^ 0xff) + 1;
    return(lrc);
  }
  
  /**
   * @brief Return true iff the given 5-byte array is a valid Advanced
   * Navigation Packet Protocol header.
   * 
   * Advanced Navigation Packet Protocol headers are five bytes long,
   * and the first byte of the header is the LRC calculated for the remaining
   * four bytes. Any five bytes where the first byte is the LRC of the next
   * four bytes is a valid ANPP header.
   * @param bytes pointer to the array containing the bytes to be tested. This
   * array *must* be at least 5 bytes long.
   * @return true iff the first 5 bytes of the array form a valid packet
   * header.
   */
  static bool IsValidHeader(const uint8_t * bytes) {
    uint8_t lrc = bytes[0];
    return(lrc == CalculateLRC(bytes + 1, 4));
  }
};

#endif /* SRC_SPATIALFOG_SPATIALFOGCORE_H_ */
