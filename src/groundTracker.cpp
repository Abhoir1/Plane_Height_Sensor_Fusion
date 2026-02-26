#include "groundTracker.h"

// Maintains a running estimate of the ground elevation above mean sea level (ASL).
// By subtracting this from the GPS altitude (also ASL), we can derive a
// GPS-based height above ground level (AGL) without relying on the altimeters.


GroundTracker::GroundTracker() : groundElevation(0.0), ready(false), count(0) {};

// Update the ground elevation estimate using a new GPS/altimeter pair.

void GroundTracker::update(double gpsAsl, double altAgl) {
	double sample = gpsAsl - altAgl;

	if (!ready) {
		groundElevation = sample;
		ready = true;
	}
	else {
		double alpha = (count < 100) ? 0.05 : 0.002;
		groundElevation = (1.0 - alpha) * groundElevation + alpha * sample;
	}

	count++;
}

// Convert a GPS ASL altitude to AGL using the tracked ground elevation.
double GroundTracker::toAgl(double gpsAsl) const {
	double agl = gpsAsl - groundElevation;

	return (agl < 0.0) ? 0.0 : agl;
}

bool GroundTracker::isReady() const {
	return ready;
}