#include <cmath>

bool isValidReading(double currValue, double prevValue, double dt, double maxRate) {
	//Basic sanity check if the value is below ground or more than max alititude

	if (currValue <= 0.0 || currValue > 200) { //200 here could be changed based on actual data
		return false;
	}

	//If the prev value was a valid entry check the rate of change of altitude

	if (!std::isnan(prevValue)) {
		double rateOfChange = std::abs(prevValue - currValue) / dt;

		if (rateOfChange > maxRate) {
			return false;
		}
	}

	return true;
}