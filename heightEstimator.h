#pragma once

class HeightEstimator {
public:
    HeightEstimator(double lowAlt, double highAlt, double alphaLow, double alphaHigh);
    double update(double fusedAltimeter, double gpsAgl);
    double getHeight() const;
    bool isInitialized() const;

private:
    double lowAlt, highAlt;
    double alphaLow, alphaHigh;
    double estimatedHeight;
    bool initialized;

    double computeBlend() const;
    double computeAlpha() const;
};
