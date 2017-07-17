
#define BOOST_TEST_MODULE libNmeaParser test
#include <boost/test/included/unit_test.hpp>
#include "NmeaComposer.h"

BOOST_AUTO_TEST_CASE( composeRMC ) {

	std::string nmeaRMC;

	std::string talkerid = "GP";
	NmeaComposerValid validity = 0L;
	boost::posix_time::time_duration mtime(16,6,18,0);
	double latitude = -12.042189972;
	double longitude = -77.14246383;
	double speedknots = 0.1;
	double coursetrue = 166.87;
	boost::gregorian::date mdate(2016,4,20);
	double magneticvar = -1.4;

	BOOST_REQUIRE_NO_THROW(NmeaComposer::composeRMC(nmeaRMC, talkerid, validity, mtime, latitude, longitude, speedknots, coursetrue, mdate, magneticvar));

}

BOOST_AUTO_TEST_CASE( composeXDR ) {

	std::string nmeaXDR;

	std::string talkerid = "WI";
	NmeaComposerValid validity = 0L;

	std::vector<TransducerMeasurement> measurements;
	TransducerMeasurement tm;

	tm.transducerType = 'C';
	tm.measurementData = 16.4;
	tm.unitsOfMeasurement = 'C';
	tm.nameOfTransducer = "TEMP";

	measurements.push_back(tm);

	tm.transducerType = 'P';
	tm.measurementData = 1.0079;
	tm.unitsOfMeasurement = 'B';
	tm.nameOfTransducer = "PRESS";

	measurements.push_back(tm);

	tm.transducerType = 'H';
	tm.measurementData = 98.9;
	tm.unitsOfMeasurement = 'P';
	tm.nameOfTransducer = "RH";

	measurements.push_back(tm);

	BOOST_REQUIRE_NO_THROW(NmeaComposer::composeXDR(nmeaXDR, talkerid, validity, measurements));

}

BOOST_AUTO_TEST_CASE( composeWMV ) {

	std::string nmeaWMV;

	std::string talkerid = "WI";
	NmeaComposerValid validity = 0L;

	double windAngle = 192.0;
	Nmea_AngleReference reference = Nmea_AngleReference_Relative;
	double windSpeed = 3.86;
	char windSpeedUnits = 'N';
	char sensorStatus = 'A';

	BOOST_REQUIRE_NO_THROW(NmeaComposer::composeMWV(nmeaWMV, talkerid, validity, windAngle, reference, windSpeed, windSpeedUnits, sensorStatus));
}

BOOST_AUTO_TEST_CASE( composeMWD ) {

	std::string nmeaMWD;

	std::string talkerid = "WI";
	NmeaComposerValid validity = 0L;

	double trueWindDirection = 4.2;
	double magneticWindDirection = 4.2;
	double windSpeedKnots = 7.2;
	double windSpeedMeters = 3.7;

	BOOST_REQUIRE_NO_THROW(NmeaComposer::composeMWD(nmeaMWD, talkerid, validity, trueWindDirection, magneticWindDirection, windSpeedKnots,	windSpeedMeters));
}

BOOST_AUTO_TEST_CASE( composeHDT ) {

	std::string nmeaHDT;

	std::string talkerid = "HE";
	NmeaComposerValid validity = 0L;

	double headingDegreesTrue = 57.34;

	BOOST_REQUIRE_NO_THROW(NmeaComposer::composeHDT(nmeaHDT, talkerid, validity, headingDegreesTrue));
}
