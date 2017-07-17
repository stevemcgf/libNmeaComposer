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
#include "NmeaEnums.h"

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
	 * @param [in]  talkerid Talker Identifier (2 characters)
	 * @param [in] 	validity Each field validity
	 * @param [in] 	mtime UTC time
	 * @param [in] 	latitude Latitude
	 * @param [in] 	longitude Longitude
	 * @param [in] 	speedknots Speed in Knots
	 * @param [in] 	coursetrue Course relative to true north
	 * @param [in] 	mdate UTC date
	 * @param [in] 	magneticvar Magnetic variation
	 *
	 */
	static void composeRMC(std::string& nmea, const std::string& talkerid,
			const NmeaComposerValid& validity,
			const boost::posix_time::time_duration& mtime,
			const double& latitude, const double& longitude,
			const double& speedknots, const double& coursetrue,
			const boost::gregorian::date& mdate, const double& magneticvar);

	/**
	 * @brief XDR NMEA Message composer
	 *
	 * <b>XDR NMEA message fields</b><br>
	 * <i>Transducer Measurement</i>
	 *
	 * Field | Meaning
	 * ------|---------
	 * 0 | Message ID --XDR
	 * 1 | Transducer Type
	 * 2 | Measurement Data
	 * 3 | Units of Measurement
	 * 4 | Name of Transducer
	 * ... | More Quadruplets like This.
	 * n | Checksum
	 *
	 * @param [out] nmea String with NMEA Sentence
	 * @param [in]  talkerid Talker Identifier (2 characters)
	 * @param [in] 	validity Each field validity
	 * @param [in]  measurements Vector of measurements. Each item have Transducer Type, Measurement Data, Units and Name of Transducer.
	 *
	 */
	static void composeXDR(std::string& nmea, const std::string& talkerid,
			const NmeaComposerValid& validity,
			std::vector<TransducerMeasurement>& measurements);

	/**
	 * @brief MWV NMEA Message composer
	 *
	 * <b>MWV NMEA message fields</b><br>
	 * <i>Wind Speed and Angle</i>
	 *
	 * Field | Meaning
	 * ------|---------
	 * 0 | Message ID $IIMWV
	 * 1 | Wind Angle, 0 to 360 degrees
	 * 2 | Reference, R = Relative, T = True
	 * 3 | Wind Speed
	 * 4 | Wind Speed Units, K = km/hr, M = m/sec, N = kt
	 * 5 | Sensor Status, A = Valid, V = Void
	 * 6 | Checksum
	 *
	 * @param [out] nmea String with NMEA Sentence
	 * @param [in]  talkerid Talker Identifier (2 characters)
	 * @param [in] 	validity Each field validity
	 * @param [in]  windAngle Wind Angle in degrees
	 * @param [in]  reference Reference True or Relative
	 * @param [in]  windSpeed Wind Speed
	 * @param [in]  windSpeedUnits Wind Speed Units
	 * @param [in]  sensorStatus Sensor Status
	 *
	 * @return Bitset each index represents the validity of each output parameter respectively.
	 */
	static void composeMWV(std::string& nmea, const std::string& talkerid,
			const NmeaComposerValid& validity, double& windAngle,
			Nmea_AngleReference& reference, double& windSpeed, char& windSpeedUnits,
			char& sensorStatus);

private:
	class impl;

	/**
	 * @brief Private constructor. Prevents creating of class instance.
	 */
	NmeaComposer();

	static void composeNmea(std::string& nmea,
			std::vector<std::string>& fields);
	static int16_t calculateNmeaChecksum(const std::string& nmeaStr);
};

#endif /* NMEACOMPOSER_H_ */
