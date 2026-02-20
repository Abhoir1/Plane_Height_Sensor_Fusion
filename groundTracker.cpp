#include "groundTracker.h"

GroundTracker::GroundTracker() : groundElevation(0.0), ready(false), count(0) {};


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

double GroundTracker::toAgl(double gpsAsl) const {
	double agl = gpsAsl - groundElevation;

	return (agl < 0.0) ? 0.0 : agl;
}

bool GroundTracker::isReady() const {
	return ready;
}