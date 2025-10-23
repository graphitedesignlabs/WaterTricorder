/*
 * Spectrometer.cpp
 * 
 * Implementation of the spectrometer sensor system.
 */

#include "Spectrometer.h"

Spectrometer::Spectrometer() {
  initialized = false;
  inSleepMode = false;
  lastReading.isValid = false;
}

bool Spectrometer::begin() {
  Serial.println("Spectrometer: Initializing...");
  
  // TODO: Initialize actual hardware
  // This is a stub implementation for the initial code structure
  // Real implementation would initialize:
  // - Light source (LED or similar)
  // - Diffraction grating
  // - Linear sensor array
  // - Wavelength calibration
  
  initializeWavelengths();
  
  lastReading.isValid = false;
  
  initialized = true;
  inSleepMode = false;
  
  Serial.println("Spectrometer: Initialized successfully");
  return true;
}

bool Spectrometer::captureSpectrum() {
  if (!initialized || inSleepMode) {
    Serial.println("Spectrometer: ERROR - Not initialized or in sleep mode");
    return false;
  }
  
  Serial.println("Spectrometer: Capturing spectrum...");
  
  // TODO: Implement actual spectral capture
  // This is a stub that generates test data
  // Real implementation would:
  // - Activate light source
  // - Read sensor array
  // - Apply wavelength calibration
  // - Process spectral data
  
  // Generate test spectrum for development
  for (int i = 0; i < SPECTRAL_BANDS; i++) {
    // Create a spectrum with some peaks (simulating absorption lines)
    float wavelength = lastReading.wavelengths[i];
    float intensity = 0.5 + 0.3 * sin(wavelength / 100.0);
    intensity += 0.1 * (random(0, 100) / 100.0); // Add some noise
    lastReading.intensities[i] = constrain(intensity, 0.0, 1.0);
  }
  
  lastReading.timestamp = millis();
  
  processSpectrum();
  
  lastReading.isValid = true;
  
  Serial.println("Spectrometer: Spectrum captured successfully");
  return true;
}

SpectralData Spectrometer::getLastReading() {
  return lastReading;
}

bool Spectrometer::isReady() {
  return initialized && !inSleepMode;
}

void Spectrometer::sleep() {
  Serial.println("Spectrometer: Entering sleep mode");
  inSleepMode = true;
  // TODO: Power down light source and sensor
}

void Spectrometer::wake() {
  Serial.println("Spectrometer: Waking from sleep mode");
  inSleepMode = false;
  // TODO: Power up light source and sensor
}

bool Spectrometer::calibrate() {
  if (!initialized) {
    return false;
  }
  
  Serial.println("Spectrometer: Calibrating...");
  
  // TODO: Implement calibration routine
  // This would include:
  // - Wavelength calibration using known reference
  // - Intensity calibration
  // - Dark current measurement
  
  Serial.println("Spectrometer: Calibration complete");
  return true;
}

float Spectrometer::getIntensityAt(float wavelength) {
  // Find closest wavelength band
  int closestBand = 0;
  float minDiff = abs(lastReading.wavelengths[0] - wavelength);
  
  for (int i = 1; i < SPECTRAL_BANDS; i++) {
    float diff = abs(lastReading.wavelengths[i] - wavelength);
    if (diff < minDiff) {
      minDiff = diff;
      closestBand = i;
    }
  }
  
  return lastReading.intensities[closestBand];
}

void Spectrometer::processSpectrum() {
  findPeak();
}

void Spectrometer::findPeak() {
  lastReading.peakIntensity = 0.0;
  lastReading.peakWavelength = 0.0;
  
  for (int i = 0; i < SPECTRAL_BANDS; i++) {
    if (lastReading.intensities[i] > lastReading.peakIntensity) {
      lastReading.peakIntensity = lastReading.intensities[i];
      lastReading.peakWavelength = lastReading.wavelengths[i];
    }
  }
}

void Spectrometer::initializeWavelengths() {
  // Initialize wavelength bands from 380nm (UV) to 750nm (red)
  // Covering the visible spectrum and near-UV
  float startWavelength = 380.0;
  float endWavelength = 750.0;
  float step = (endWavelength - startWavelength) / (SPECTRAL_BANDS - 1);
  
  for (int i = 0; i < SPECTRAL_BANDS; i++) {
    lastReading.wavelengths[i] = startWavelength + (i * step);
  }
}
