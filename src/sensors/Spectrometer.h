/*
 * Spectrometer.h
 * 
 * Interface for the spectrometer sensor system.
 * Captures spectral data to detect toxic inorganic compounds.
 * 
 * Design inspiration from Public Lab's DIY spectrometer.
 */

#ifndef SPECTROMETER_H
#define SPECTROMETER_H

#include <Arduino.h>

// Number of wavelength bands to measure
#define SPECTRAL_BANDS 64

// Structure to hold spectral data
struct SpectralData {
  float intensities[SPECTRAL_BANDS]; // Intensity for each wavelength band
  float wavelengths[SPECTRAL_BANDS]; // Center wavelength for each band (nm)
  float peakWavelength;              // Wavelength with highest intensity
  float peakIntensity;               // Maximum intensity
  unsigned long timestamp;
  bool isValid;
};

class Spectrometer {
  public:
    Spectrometer();
    
    // Initialize the spectrometer
    bool begin();
    
    // Capture spectral data
    bool captureSpectrum();
    
    // Get the last captured data
    SpectralData getLastReading();
    
    // Check if sensor is ready
    bool isReady();
    
    // Put sensor in low power mode
    void sleep();
    
    // Wake sensor from low power mode
    void wake();
    
    // Calibrate the sensor
    bool calibrate();
    
    // Get intensity at specific wavelength
    float getIntensityAt(float wavelength);
    
  private:
    SpectralData lastReading;
    bool initialized;
    bool inSleepMode;
    
    // Internal helper functions
    void processSpectrum();
    void findPeak();
    void initializeWavelengths();
};

#endif // SPECTROMETER_H
