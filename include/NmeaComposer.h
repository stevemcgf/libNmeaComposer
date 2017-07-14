/*
 * NmeaComposer.h
 *
 *  Created on: Jul 14, 2017
 *      Author: steve
 */

#ifndef NMEACOMPOSER_H_
#define NMEACOMPOSER_H_

#include <vector>
#include <string>
#include <boost/date_time.hpp>
#include <bitset>

typedef std::bitset<16> NmeaComposerValid; //!<  Bitset. Each index represents the validity of each input parameter.

class NmeaComposer {
public:

	/**
	 * @brief RMC NMEA Message composer
	 *
	 * <b>RMC NMEA message fields</b><br>
	 * <i>Recommended Minimum Navigation Information</i>
	 *
	 * Field | Meaning
	 * ------|---------
	 * 0 | Message ID $--RMC
	 * 1 | UTC of position fix
	 * 2 | Status A=active or V=void
	 * 3 | Latitude
	 * 4 | Direction of latitude: N: North S: South
	 * 5 | Longitude
	 * 6 | Direction of longitude: E: East W: West
	 * 7 | Speed over the ground in knots
	 * 8 | Course over ground, degrees true
	 * 9 | Date
	 * 10 | Magnetic variation
	 * 11 | degrees E/W
	 * 12 | Mode indicator
	 * 13 | Navigational status
	 * 14 | The checksum data, always begins with *
	 *
	 * @param [out] nmea String with NMEA Sentence
	 * @param [in] 	validity Each field validity
	 * @param [in] 	mtime UTC time
	 * @param [in] 	latitude Latitude
	 * @param [in] 	longitude Longitude
	 * @param [in] 	speedknots Speed in Knots
	 * @param [in] 	coursetrue Course relative to true north
	 * @param [in] 	mdate UTC date
	 * @param [in] 	magneticvar Magnetic variation
	 *
	 * @return Bitset each index represents the validity of each output parameter respectively.
	 */
	static void composeRMC(std::string& nmea, const NmeaComposerValid& validity,
			const boost::posix_time::time_duration& mtime, const double& latitude,
			const double& longitude, const double& speedknots, const double& coursetrue,
			const boost::gregorian::date& mdate, const double& magneticvar);

private:
	class impl;

	/**
	 * @brief Private constructor. Prevents creating of class instance.
	 */
	NmeaComposer();
};

#endif /* NMEACOMPOSER_H_ */
