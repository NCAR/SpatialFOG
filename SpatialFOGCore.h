// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
/*
 * SpatialFOGCore.h
 *
 *  Created on: May 27, 2016
 *      Author: burghart
 */

#include <cstdint>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

#ifndef SRC_SPATIALFOG_SPATIALFOGCORE_H_
#define SRC_SPATIALFOG_SPATIALFOGCORE_H_

/**
 * @brief SpatialFOGCore provides the business-knowledge core for configuring
 * a SpatialFOG INS unit and for interpreting its data packets.
 */
class SpatialFOGCore {
public:
  /**
   * @brief Instantiate for a SpatialFOG with given unit orientation and offset
   * to the GNSS antenna.
   * 
   * The orientation is defined starting from  the default installation 
   * orientation, and assumes that the device is first rotated 
   * orientationHeadingDeg degrees about the INS z axis, then 
   * orientationPitchDeg degrees about the INS y axis, then
   * orientationRollDeg degrees about the INS x axis.
   * 
   * Antenna offsets are given in meters between the center of the SpatialFOG
   * unit and the bottom center of the GNSS antenna, and are specified using
   * the *body* (aircraft or pod) axes, i.e., positive X is forward, positive
   * Y is right, and positive Z is down.
   * 
   * @param orientationHeadingDeg unit's rotation in degrees about its z axis 
   * relative its default orientation. This rotation is applied first.
   * @param orientationPitchDeg unit's rotation in degrees about its y axis
   * relative to its default orientation. This rotation is applied second.
   * @param orientationRollDeg unit's rotation in degrees about its x axis
   * relative to its default orientation. This rotation is applied third.
   * @param antOffsetX offset in meters between the center of the SpatialFOG
   * and the bottom center of the GNSS antenna along the *body* (aircraft or
   * pod) X axis, i.e., forward
   * @param antOffsetY offset in meters between the center of the SpatialFOG
   * and the bottom center of the GNSS antenna along the *body* (aircraft or
   * pod) Y axis, i.e., right
   * @param antOffsetZ offset in meters between the center of the SpatialFOG
   * and the bottom center of the GNSS antenna along the *body* (aircraft or
   * pod) Z axis, i.e., down
   */
  SpatialFOGCore(float orientationHeadingDeg, 
                 float orientationPitchDeg,
                 float orientationRollDeg,
                 float antOffsetX,
                 float antOffsetY,
                 float antOffsetZ);

  /**
   * @brief Destructor
   */
  virtual ~SpatialFOGCore();

private:

  /// @brief Boolean set to true when the SpatialFOG's current configuration
  /// matches the desired configuration.
  bool _configurationComplete;

  /// @brief Vector of sent configuration packet IDs for which acknowledgments
  /// are expected.
  std::vector<uint8_t> _expectedAcks;
};

#endif /* SRC_SPATIALFOG_SPATIALFOGCORE_H_ */
