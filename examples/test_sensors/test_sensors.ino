/*
 * Test Sensors Example
 * 
 * This example demonstrates basic sensor functionality
 * and can be used to verify the hardware setup.
 */

#include "../../src/sensors/OpticalSensor.h"
#include "../../src/sensors/Spectrometer.h"

OpticalSensor opticalSensor;
Spectrometer spectrometer;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 5000);
  
  Serial.println("Water Tricorder - Sensor Test");
  Serial.println("==============================");
  
  // Initialize optical sensor
  Serial.println("\nInitializing Optical Sensor...");
  if (opticalSensor.begin()) {
    Serial.println("✓ Optical sensor initialized");
  } else {
    Serial.println("✗ Optical sensor initialization failed");
  }
  
  // Initialize spectrometer
  Serial.println("\nInitializing Spectrometer...");
  if (spectrometer.begin()) {
    Serial.println("✓ Spectrometer initialized");
  } else {
    Serial.println("✗ Spectrometer initialization failed");
  }
  
  Serial.println("\n==============================");
  Serial.println("Setup complete. Starting tests...\n");
}

void loop() {
  // Test optical sensor
  Serial.println("Testing Optical Sensor:");
  if (opticalSensor.captureImage()) {
    OpticalData data = opticalSensor.getLastReading();
    Serial.print("  Image size: ");
    Serial.print(data.imageWidth);
    Serial.print("x");
    Serial.println(data.imageHeight);
    Serial.print("  Average brightness: ");
    Serial.println(data.averageBrightness);
    Serial.print("  Contrast: ");
    Serial.println(data.contrast);
    Serial.print("  Valid: ");
    Serial.println(data.isValid ? "Yes" : "No");
  } else {
    Serial.println("  Capture failed!");
  }
  
  Serial.println();
  
  // Test spectrometer
  Serial.println("Testing Spectrometer:");
  if (spectrometer.captureSpectrum()) {
    SpectralData data = spectrometer.getLastReading();
    Serial.print("  Spectral bands: ");
    Serial.println(SPECTRAL_BANDS);
    Serial.print("  Peak wavelength: ");
    Serial.print(data.peakWavelength);
    Serial.println(" nm");
    Serial.print("  Peak intensity: ");
    Serial.println(data.peakIntensity);
    Serial.print("  Valid: ");
    Serial.println(data.isValid ? "Yes" : "No");
    
    // Print first few bands
    Serial.println("  First 5 bands:");
    for (int i = 0; i < 5; i++) {
      Serial.print("    ");
      Serial.print(data.wavelengths[i]);
      Serial.print(" nm: ");
      Serial.println(data.intensities[i]);
    }
  } else {
    Serial.println("  Capture failed!");
  }
  
  Serial.println("\n==============================\n");
  
  // Wait before next test
  delay(5000);
}
