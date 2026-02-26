#include "outlierRejection.h"
#include <cmath>

// Validates individual altimeter readings by checking for physically impossible values.
// Two failure modes are caught:
//   1. Below-ground readings (<=0): sensor dropout or hardware fault
//   2. Excessive rate of change: reading jumped too far since the last valid sample.

bool isValidReading(double currValue, double prevValue, double dt, double maxRate) {
	//Basic sanity check if the value is below ground or more than max altitude

	if (currValue <= 0.0 || currValue > 200.0) { //200 here could be changed based on actual data
		return false;
	}

	//If the prev value was a valid entry check the rate of change of altitude

	if (!std::isnan(prevValue)) {
		double rateOfChange = std::abs(prevValue - currValue) / dt;

		if (rateOfChange > maxRate) { //if this change is physically not possible reject the reading
			return false;
		}
	}

	return true;
}