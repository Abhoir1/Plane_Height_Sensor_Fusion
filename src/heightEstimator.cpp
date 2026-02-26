#include "heightEstimator.h"
#include <algorithm>

// Combines the fused altimeter reading and GPS-derived AGL into a single
// smooth height estimate using altitude-dependent blending and adaptive EMA.

HeightEstimator::HeightEstimator(double lowAlt, double highAlt, double alphaLow, double alphaHigh)
    : lowAlt(lowAlt), highAlt(highAlt), alphaLow(alphaLow), alphaHigh(alphaHigh),
    estimatedHeight(0.0), initialized(false) {
}

// Blending logic:
//   - Below LOW_ALT:  fully trust altimeters (precise ground-following for spraying)
//   - Above HIGH_ALT: fully trust GPS AGL (smooth trajectory over rough terrain)
//   - Between:        linearly interpolate between the two
double HeightEstimator::computeBlend() const {
    if (estimatedHeight <= lowAlt)  return 1.0;
    if (estimatedHeight > highAlt)  return 0.0;
    return 1.0 - (estimatedHeight - lowAlt) / (highAlt - lowAlt);
}

// Smoothing logic:
//   - alphaLow applied below LOW_ALT  (more responsive, reacts to terrain quickly)
//   - alphaHigh applied above HIGH_ALT (heavier smoothing for a smooth flight path)
//   - Linearly interpolated in the transition zone
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

    //EMA
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