
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
