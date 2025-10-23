/*
 * OpticalSensor.h
 * 
 * Interface for the optical microscopy sensor system.
 * Captures images of water samples to detect microorganisms.
 * 
 * Design requirements:
 * - Portable microscope with sufficient magnification (1000x or more)
 * - May use darkfield microscopy for enhanced bacteria visibility
 * - Low maintenance lens design
 * - Feeds ML system for bacteriological pathogen recognition
 */

#ifndef OPTICAL_SENSOR_H
#define OPTICAL_SENSOR_H

#include <Arduino.h>

// Structure to hold optical sensor data
struct OpticalData {
  uint8_t imageData[128 * 128]; // 128x128 grayscale image
  uint16_t imageWidth;
  uint16_t imageHeight;
  float averageBrightness;
  float contrast;
  unsigned long timestamp;
  bool isValid;
};

class OpticalSensor {
  public:
    OpticalSensor();
    
    // Initialize the optical sensor
    bool begin();
    
    // Capture an image from the optical sensor
    bool captureImage();
    
    // Get the last captured data
    OpticalData getLastReading();
    
    // Check if sensor is ready
    bool isReady();
    
    // Put sensor in low power mode
    void sleep();
    
    // Wake sensor from low power mode
    void wake();
    
    // Calibrate the sensor
    bool calibrate();
    
  private:
    OpticalData lastReading;
    bool initialized;
    bool inSleepMode;
    
    // Internal helper functions
    void processImage();
    float calculateBrightness();
    float calculateContrast();
    void clearImageBuffer();
};

#endif // OPTICAL_SENSOR_H
