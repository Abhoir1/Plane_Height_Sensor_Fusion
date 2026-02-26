#include "heightEstimator.h"
#include <algorithm>

HeightEstimator::HeightEstimator(double lowAlt, double highAlt, double alphaLow, double alphaHigh)
    : lowAlt(lowAlt), highAlt(highAlt), alphaLow(alphaLow), alphaHigh(alphaHigh),
    estimatedHeight(0.0), initialized(false) {
}

double HeightEstimator::computeBlend() const {
    if (estimatedHeight <= lowAlt)  return 1.0;
    if (estimatedHeight > highAlt)  return 0.0;
    return 1.0 - (estimatedHeight - lowAlt) / (highAlt - lowAlt);
}

double HeightEstimator::computeAlpha() const {
    if (estimatedHeight <= lowAlt) return alphaLow;
    double t = std::min(1.0, (estimatedHeight - lowAlt) / (highAlt - lowAlt));
    return alphaLow * (1.0 - t) + alphaHigh * t;
}

double HeightEstimator::update(double fusedAltimeter, double gpsAgl) {
    // Seed on first valid reading
    if (!initialized && fusedAltimeter >= 0) {
        estimatedHeight = fusedAltimeter;
        initialized = true;
        return estimatedHeight;
    }

    double blend = computeBlend();
    double target = estimatedHeight;

    if (fusedAltimeter >= 0 && gpsAgl >= 0)
        target = blend * fusedAltimeter + (1.0 - blend) * gpsAgl;
    else if (fusedAltimeter >= 0)
        target = fusedAltimeter;
    else if (gpsAgl >= 0)
        target = gpsAgl;

    double alpha = computeAlpha();
    estimatedHeight = alpha * target + (1.0 - alpha) * estimatedHeight;
    return estimatedHeight;
}

double HeightEstimator::getHeight() const { return estimatedHeight; }
bool HeightEstimator::isInitialized() const { return initialized; }