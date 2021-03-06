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
			const double latitude, const double longitude,
			const double speedknots, const double coursetrue,
			const boost::gregorian::date& mdate, const double magneticvar);

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
			const std::vector<TransducerMeasurement>& measurements);

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
	 */
	static void composeMWV(std::string& nmea, const std::string& talkerid,
			const NmeaComposerValid& validity, const double windAngle,
			const Nmea_AngleReference reference, const double windSpeed,
			const char windSpeedUnits, const char sensorStatus);

	/**
	 * @brief MWD NMEA Message composer
	 *
	 * <b>MWD NMEA message fields</b><br>
	 * <i>Wind Direction & Speed</i>
	 *
	 * Field | Meaning
	 * ------|---------
	 * 0 | Message ID --MWD
	 * 1 | Wind direction, 0° to 359º
	 * 2 | True
	 * 3 | Wind direction, 0° to 359º
	 * 4 | Magnetic
	 * 5 | Wind speed in Knots
	 * 6 | Knots
	 * 7 | Wind speed in Meters per second
	 * 8 | meters/second
	 * 9 | checksum
	 *
	 * @param [out] nmea String with NMEA Sentence
	 * @param [in]  talkerid Talker Identifier (2 characters)
	 * @param [in] 	validity Each field validity
	 * @param [in]  trueWindDirection Wind Direction in Degrees relative to True North.
	 * @param [in]  magneticWindDirection Wind Direction in Degrees relative to Magnetic North.
	 * @param [in]  windSpeedKnots Wind Speed in Knots.
	 * @param [in]  windSpeedMeters Wind Speed in Meters per second.
	 *
	 */
	static void composeMWD(std::string& nmea, const std::string& talkerid,
			const NmeaComposerValid& validity, const double trueWindDirection,
			const double magneticWindDirection, const double windSpeedKnots,
			const double windSpeedMeters);

	/**
	 * @brief HDT NMEA Message composer
	 *
	 * <b>HDT NMEA message fields</b><br>
	 * <i>Heading - 1</i>
	 *
	 * Field | Meaning
	 * ------|---------
	 * 0 | Message ID $HCHDT
	 * 1 | Heading Degrees, true
	 * 2 | T = True
	 * 3 | Checksum
	 *
	 * @param [out] nmea String with NMEA Sentence
	 * @param [in]  talkerid Talker Identifier (2 characters)
	 * @param [in] 	validity Each field validity
	 * @param [in]  headingDegreesTrue Heading degrees relative to true north
	 *
	 */
	static void composeHDT(std::string& nmea, const std::string& talkerid,
			const NmeaComposerValid& validity, const double headingDegreesTrue);

	/**
	 * @brief VLW NMEA Message composer
	 *
	 * <b>VLW NMEA message fields</b><br>
	 * <i>Distance Traveled through Water</i>
	 *
	 * Field | Meaning
	 * ------|---------
	 * 0 | Message ID $VDVLW
	 * 1 | Total cumulative distance
	 * 2 | N = Nautical Miles
	 * 3 | Distance since Reset
	 * 4 | N = Nautical Miles
	 * 5 | Checksum
	 *
	 * @param [out] nmea String with NMEA Sentence
	 * @param [in]  talkerid Talker Identifier (2 characters)
	 * @param [in] 	validity Each field validity
	 * @param [in]  totalCumulativeDistance Total cumulative distance in Nautical Miles
	 * @param [in]  distanceSinceReset Distance since reset in Nautical Miles
	 *
	 */
	static void composeVLW(std::string& nmea, const std::string& talkerid,
			const NmeaComposerValid& validity,
			const double totalCumulativeDistance,
			const double distanceSinceReset);

	/**
	 * @brief VHW NMEA Message composer
	 *
	 * <b>VHW NMEA message fields</b><br>
	 * <i>Water speed and heading</i>
	 *
	 * Field | Meaning
	 * ------|---------
	 * 0 | Message ID $VDVHW
	 * 1 | Degress True
	 * 2 | T = True
	 * 3 | Degrees Magnetic
	 * 4 | M = Magnetic
	 * 5 | Knots (speed of vessel relative to the water)
	 * 6 | N = Knots
	 * 7 | Kilometers (speed of vessel relative to the water)
	 * 8 | K = Kilometres
	 * 9 | Checksum
	 *
	 * @param [out] nmea String with NMEA Sentence
	 * @param [in]  talkerid Talker Identifier (2 characters)
	 * @param [in] 	validity Each field validity
	 * @param [in]  headingTrue Heading degrees true
	 * @param [in]  headingMagnetic Heading magnetic true
	 * @param [in]  speedInKnots Speed in Knots
	 * @param [in]  speedInKmH Speed in Km/h
	 *
	 */
	static void composeVHW(std::string& nmea, const std::string& talkerid,
			const NmeaComposerValid& validity, const double headingTrue,
			const double headingMagnetic, const double speedInKnots,
			const double speedInKmH);

	/**
	 * @brief PRDID NMEA Message composer
	 *
	 * <b>PRDID NMEA message fields</b><br>
	 * <i>Proprietary Heading, Pitch, Roll</i>
	 *
	 * Field | Meaning
	 * ------|---------
	 * 0 | Message ID PRDID
	 * 1 | Pitch
	 * 2 | Roll
	 * 3 | Heading
	 * 4 | Checksum
	 *
	 * @param [out] nmea String with NMEA Sentence
	 * @param [in]  talkerid Talker Identifier (2 characters)
	 * @param [in] 	validity Each field validity
	 * @param [in]  pitch Is the up/down rotation of a vessel about its lateral/Y (side-to-side or port-starboard) axis.
	 * @param [in]  roll Is the tilting rotation of a vessel about its longitudinal/X (front-back or bow-stern) axis.
	 * @param [in]  heading Is the north direction of a vessel.
	 *
	 */
	static void composePRDID(std::string& nmea,
			const NmeaComposerValid& validity, const double pitch,
			const double roll, const double heading);

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
