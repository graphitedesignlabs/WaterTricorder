/*
 * Water Tricorder - Main Application
 * 
 * A low-cost opensource device for quickly and reliably answering:
 * "Can I drink this water?"
 * 
 * Hardware: Arduino Nano 33 BLE Sense
 * 
 * This device uses:
 * - Optical microscopy for detecting harmful microorganisms
 * - Spectrometry for measuring toxic inorganic compounds
 * - On-device machine learning (TensorFlow Lite) for instant analysis
 */

#include "src/sensors/OpticalSensor.h"
#include "src/sensors/Spectrometer.h"
#include "src/ml/WaterQualityClassifier.h"
#include "src/ui/Display.h"
#include "src/power/PowerManager.h"

// Global sensor and system objects
OpticalSensor opticalSensor;
Spectrometer spectrometer;
WaterQualityClassifier classifier;
Display display;
PowerManager powerManager;

// System states
enum SystemState {
  STATE_IDLE,
  STATE_SAMPLING,
  STATE_ANALYZING,
  STATE_DISPLAYING_RESULTS,
  STATE_LOW_POWER
};

SystemState currentState = STATE_IDLE;

// Water quality result
struct WaterQualityResult {
  bool isPotable;
  float confidence;
  float bacteriaLevel;
  float toxicCompoundsLevel;
  char warnings[256];
};

WaterQualityResult lastResult;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 5000); // Wait up to 5 seconds for serial
  
  Serial.println("Water Tricorder - Initializing...");
  
  // Initialize power management
  if (!powerManager.begin()) {
    Serial.println("ERROR: Power manager initialization failed!");
    displayError("Power Init Failed");
    return;
  }
  
  // Initialize display
  if (!display.begin()) {
    Serial.println("ERROR: Display initialization failed!");
    // Continue without display
  }
  
  display.showSplashScreen();
  delay(2000);
  
  // Initialize sensors
  Serial.println("Initializing optical sensor...");
  if (!opticalSensor.begin()) {
    Serial.println("ERROR: Optical sensor initialization failed!");
    displayError("Optical Sensor Failed");
  }
  
  Serial.println("Initializing spectrometer...");
  if (!spectrometer.begin()) {
    Serial.println("ERROR: Spectrometer initialization failed!");
    displayError("Spectrometer Failed");
  }
  
  // Initialize ML classifier
  Serial.println("Loading ML model...");
  if (!classifier.begin()) {
    Serial.println("ERROR: ML classifier initialization failed!");
    displayError("ML Model Failed");
  }
  
  Serial.println("Water Tricorder ready!");
  display.showIdleScreen();
  currentState = STATE_IDLE;
}

void loop() {
  // Check power level
  if (powerManager.isBatteryLow()) {
    enterLowPowerMode();
    return;
  }
  
  switch (currentState) {
    case STATE_IDLE:
      handleIdleState();
      break;
      
    case STATE_SAMPLING:
      handleSamplingState();
      break;
      
    case STATE_ANALYZING:
      handleAnalyzingState();
      break;
      
    case STATE_DISPLAYING_RESULTS:
      handleDisplayingResultsState();
      break;
      
    case STATE_LOW_POWER:
      handleLowPowerState();
      break;
  }
  
  delay(10); // Small delay to prevent excessive CPU usage
}

void handleIdleState() {
  // Check for button press or trigger to start sampling
  if (display.isTestButtonPressed()) {
    Serial.println("Starting water quality test...");
    display.showSamplingScreen();
    currentState = STATE_SAMPLING;
  }
}

void handleSamplingState() {
  Serial.println("Collecting sensor data...");
  
  // Capture optical data for microorganism detection
  Serial.println("  - Capturing microscopy image...");
  if (!opticalSensor.captureImage()) {
    Serial.println("ERROR: Failed to capture optical data");
    displayError("Optical Capture Failed");
    currentState = STATE_IDLE;
    return;
  }
  
  // Capture spectral data for inorganic compound detection
  Serial.println("  - Capturing spectral data...");
  if (!spectrometer.captureSpectrum()) {
    Serial.println("ERROR: Failed to capture spectral data");
    displayError("Spectral Capture Failed");
    currentState = STATE_IDLE;
    return;
  }
  
  Serial.println("Sensor data collected successfully");
  display.showAnalyzingScreen();
  currentState = STATE_ANALYZING;
}

void handleAnalyzingState() {
  Serial.println("Analyzing water quality...");
  
  // Get sensor data
  OpticalData opticalData = opticalSensor.getLastReading();
  SpectralData spectralData = spectrometer.getLastReading();
  
  // Run ML classification
  lastResult = classifier.classifyWaterQuality(opticalData, spectralData);
  
  // Log results
  Serial.println("Analysis complete:");
  Serial.print("  Potable: ");
  Serial.println(lastResult.isPotable ? "YES" : "NO");
  Serial.print("  Confidence: ");
  Serial.print(lastResult.confidence * 100);
  Serial.println("%");
  Serial.print("  Bacteria Level: ");
  Serial.println(lastResult.bacteriaLevel);
  Serial.print("  Toxic Compounds Level: ");
  Serial.println(lastResult.toxicCompoundsLevel);
  
  if (strlen(lastResult.warnings) > 0) {
    Serial.print("  Warnings: ");
    Serial.println(lastResult.warnings);
  }
  
  display.showResults(lastResult);
  currentState = STATE_DISPLAYING_RESULTS;
}

void handleDisplayingResultsState() {
  // Display results for configured duration
  static unsigned long displayStartTime = millis();
  
  if (millis() - displayStartTime > 30000) { // Display for 30 seconds
    displayStartTime = millis();
    display.showIdleScreen();
    currentState = STATE_IDLE;
  }
  
  // Allow early exit if button pressed
  if (display.isTestButtonPressed()) {
    displayStartTime = millis();
    display.showIdleScreen();
    currentState = STATE_IDLE;
  }
}

void handleLowPowerState() {
  // In low power mode, minimize activity
  powerManager.sleep(1000); // Sleep for 1 second
  
  // Check if power has been restored
  if (!powerManager.isBatteryLow()) {
    currentState = STATE_IDLE;
    display.showIdleScreen();
  }
}

void enterLowPowerMode() {
  Serial.println("Entering low power mode...");
  display.showLowPowerWarning();
  delay(2000);
  display.sleep();
  opticalSensor.sleep();
  spectrometer.sleep();
  currentState = STATE_LOW_POWER;
}

void displayError(const char* message) {
  Serial.print("ERROR: ");
  Serial.println(message);
  display.showError(message);
  delay(3000);
}
