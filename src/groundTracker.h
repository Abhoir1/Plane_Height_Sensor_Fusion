#pragma once

class GroundTracker {
public:
	GroundTracker();

	void update(double gpsASL, double altAgl);
	double toAgl(double gpsASL) const;
	bool isReady() const;

private:
	double groundElevation;
	bool ready;
	int count;
};