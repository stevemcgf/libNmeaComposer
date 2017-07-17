/*
 * NmeaComposer.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: steve
 */

#include "NmeaComposer.h"

#include <iomanip>
#include <boost/format.hpp>
#include <boost/format/group.hpp>
#include <boost/log/trivial.hpp>

/// @cond
#ifdef NP_DEBUG
#define LOG_MESSAGE(lvl) BOOST_LOG_TRIVIAL(lvl)
#else
#define LOG_MESSAGE(lvl) if (false) BOOST_LOG_TRIVIAL(lvl)
#endif
/// @endcond

NmeaComposer::NmeaComposer() {

}

int16_t NmeaComposer::calculateNmeaChecksum(const std::string& nmeaStr) {
	int16_t checksum = 0;
	for (uint i = 1; i < nmeaStr.length() - 1; ++i) {
		checksum ^= nmeaStr[i];
	}
	return checksum;
}

void NmeaComposer::composeNmea(std::string& nmea, std::vector<std::string>& fields)
{
	nmea.append("$");

	for (uint i = 0; i < fields.size(); ++i)
	{
		nmea.append(fields[i]);
		if (i < fields.size() - 1)
		{
			nmea.append(",");
		} else {
			nmea.append("*");
		}
		LOG_MESSAGE(debug) << fields[i];
	}
	int16_t checksum = calculateNmeaChecksum(nmea);

	boost::format auxfmt("%02X");
	nmea.append(boost::str(auxfmt % checksum));
}

void NmeaComposer::composeRMC(std::string& nmea, const std::string& talkerid,
		const NmeaComposerValid& validity,
		const boost::posix_time::time_duration& mtime,
		const double& latitude, const double& longitude,
		const double& speedknots, const double& coursetrue,
		const boost::gregorian::date& mdate, const double& magneticvar)
{
	int idxVar = 0;
	std::vector<std::string> fields;
	nmea = "";
	nmea.reserve(128);

	/*------------ Field 00 ---------------*/
	if (talkerid.length() == 2)
	{
		std::string nmeahead;
		nmeahead.reserve(8);
		nmeahead.append(talkerid);
		nmeahead.append("RMC");
		fields.push_back(nmeahead);
	} else {
		// Error
	}

	/*------------ Field 01 ---------------*/
	if (!validity[idxVar])
	{
		boost::format auxfmt("%02i%02i%02i.%03i");

		fields.push_back(boost::str(auxfmt % mtime.hours() % mtime.minutes() % mtime.seconds() % (mtime.fractional_seconds() / 1000)));
	} else {
		fields.push_back("");
	}
	++idxVar;

	/*------------ Field 02 ---------------*/
	fields.push_back("A");

	/*------------ Field 03,04 ---------------*/
	if (!validity[idxVar])
	{
		boost::format auxfmt("%02i%010.7f");

		double abslatitude = std::abs(latitude);
		double degrees;
		double minutes;
		minutes = std::modf(abslatitude, &degrees) * 60.0f;

		fields.push_back(boost::str(auxfmt % degrees % minutes));

		if (latitude < 0) {
			fields.push_back("S");
		} else {
			fields.push_back("N");
		}
	}  else {
		fields.push_back("");
		fields.push_back("");
	}
	++idxVar;

	/*------------ Field 05,06 ---------------*/
	if (!validity[idxVar])
	{
		boost::format auxfmt("%03i%010.7f");

		double abslongitude = std::abs(longitude);
		double degrees;
		double minutes;
		minutes = std::modf(abslongitude, &degrees) * 60.0f;

		fields.push_back(boost::str(auxfmt % degrees % minutes));

		if (longitude < 0) {
			fields.push_back("W");
		} else {
			fields.push_back("E");
		}
	}  else {
		fields.push_back("");
		fields.push_back("");
	}
	++idxVar;

	/*------------ Field 07 ---------------*/
	if (!validity[idxVar])
	{
		boost::format auxfmt("%.2f");

		fields.push_back(boost::str(auxfmt % speedknots));
	}
	++idxVar;

	/*------------ Field 08 ---------------*/
	if (!validity[idxVar])
	{
		boost::format auxfmt("%.2f");

		fields.push_back(boost::str(auxfmt % coursetrue));
	}
	++idxVar;

	/*------------ Field 09 ---------------*/
	if (!validity[idxVar])
	{
		boost::format auxfmt("%02i%02i%02i");

		fields.push_back(boost::str(auxfmt % mdate.day() % static_cast<int>(mdate.month()) % (mdate.year() % 100)));
	}
	++idxVar;

	/*------------ Field 10,11 ---------------*/
	if (!validity[idxVar])
	{
		boost::format auxfmt("%.1f");

		double absmagneticvar = std::abs(magneticvar);

		fields.push_back(boost::str(auxfmt % absmagneticvar));

		if (magneticvar < 0)
		{
			fields.push_back("W");
		} else {
			fields.push_back("E");
		}
	}

	/*------------ Field 12 ---------------*/
	fields.push_back("A");

	composeNmea(nmea, fields);

	LOG_MESSAGE(debug) << nmea;
}

void NmeaComposer::composeXDR(std::string& nmea, const std::string& talkerid,
			const NmeaComposerValid& validity, std::vector<TransducerMeasurement>& measurements)
{
	int idxVar = 0;
	std::vector<std::string> fields;
	nmea = "";
	nmea.reserve(128);

	/*------------ Field 00 ---------------*/
	if (talkerid.length() == 2)
	{
		std::string nmeahead;
		nmeahead.reserve(8);
		nmeahead.append(talkerid);
		nmeahead.append("XDR");
		fields.push_back(nmeahead);
	} else {
		// Error
	}

	for (auto& tm : measurements)
	{
		/*------------ Field 01 ---------------*/
		if (!validity[idxVar])
		{
			fields.emplace_back(&tm.transducerType, 1);
		} else {
			fields.push_back("");
		}
		++idxVar;

		/*------------ Field 02 ---------------*/
		if (!validity[idxVar])
		{
			boost::format auxfmt;
			if (tm.unitsOfMeasurement == 'C')
			{
				auxfmt = boost::format("%+06.1f");
			} else if (tm.unitsOfMeasurement == 'B') {
				auxfmt = boost::format("%6.4f");
			} else if (tm.unitsOfMeasurement == 'P') {
				auxfmt = boost::format("%05.1f");
			} else {
				auxfmt = boost::format("%.1f");
			}

			fields.push_back(boost::str(auxfmt % tm.measurementData));
		} else {
			fields.push_back("");
		}
		++idxVar;

		/*------------ Field 03 ---------------*/
		if (!validity[idxVar])
		{
			fields.emplace_back(&tm.unitsOfMeasurement, 1);
		} else {
			fields.push_back("");
		}
		++idxVar;

		/*------------ Field 04 ---------------*/
		if (!validity[idxVar])
		{
			fields.push_back(tm.nameOfTransducer);
		} else {
			fields.push_back("");
		}
		++idxVar;
	}

	composeNmea(nmea, fields);

	LOG_MESSAGE(debug) << nmea;
}

void NmeaComposer::composeMWV(std::string& nmea, const std::string& talkerid,
			const NmeaComposerValid& validity, double& windAngle,
			Nmea_AngleReference& reference, double& windSpeed, char& windSpeedUnits,
			char& sensorStatus)
{
	int idxVar = 0;
	std::vector<std::string> fields;
	nmea = "";
	nmea.reserve(128);

	/*------------ Field 00 ---------------*/
	if (talkerid.length() == 2)
	{
		std::string nmeahead;
		nmeahead.reserve(8);
		nmeahead.append(talkerid);
		nmeahead.append("MWV");
		fields.push_back(nmeahead);
	} else {
		// Error
	}

	/*------------ Field 01 ---------------*/
	if (!validity[idxVar])
	{
		boost::format auxfmt("%05.1f");

		fields.push_back(boost::str(auxfmt % windAngle));
	} else {
		fields.push_back("");
	}
	++idxVar;

	/*------------ Field 02 ---------------*/
	if (!validity[idxVar])
	{
		if (reference == Nmea_AngleReference_True)
		{
			fields.push_back("T");
		} else {
			fields.push_back("R");
		}
	} else {
		fields.push_back("");
	}
	++idxVar;

	/*------------ Field 03 ---------------*/
	if (!validity[idxVar])
	{
		boost::format auxfmt("%05.1f");

		fields.push_back(boost::str(auxfmt % windSpeed));
	} else {
		fields.push_back("");
	}
	++idxVar;

	/*------------ Field 03 ---------------*/
	if (!validity[idxVar])
	{
		fields.emplace_back(&windSpeedUnits, 1);
	} else {
		fields.push_back("");
	}
	++idxVar;

	/*------------ Field 04 ---------------*/
	if (!validity[idxVar])
	{
		fields.emplace_back(&sensorStatus, 1);
	} else {
		fields.push_back("");
	}
	++idxVar;

	composeNmea(nmea, fields);

	LOG_MESSAGE(debug) << nmea;
}
