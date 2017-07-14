/*
 * NmeaComposer.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: steve
 */

#include "NmeaComposer.h"

NmeaComposer::NmeaComposer() {

}

void NmeaComposer::composeRMC(std::string& nmea, const NmeaComposerValid& validity,
			const boost::posix_time::time_duration& mtime, const double& latitude,
			const double& longitude, const double& speedknots, const double& coursetrue,
			const boost::gregorian::date& mdate, const double& magneticvar)
{

}
