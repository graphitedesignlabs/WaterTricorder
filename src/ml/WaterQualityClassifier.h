/*
 * WaterQualityClassifier.h
 * 
 * Machine learning classifier for water quality assessment.
 * Uses TensorFlow Lite for Microcontrollers to analyze sensor data.
 * 
 * Analyzes:
 * - Optical data (microscopy images) for microorganism detection
 * - Spectral data for toxic inorganic compound detection
 * 
 * Output: Simple yes/no answer to "Can I drink this water?"
 */

#ifndef WATER_QUALITY_CLASSIFIER_H
#define WATER_QUALITY_CLASSIFIER_H

#include <Arduino.h>
#include "../sensors/OpticalSensor.h"
#include "../sensors/Spectrometer.h"

// Classification result structure
struct ClassificationResult {
  bool isPotable;               // Can the water be consumed safely?
  float confidence;             // Confidence level (0.0 to 1.0)
  float bacteriaLevel;          // Estimated bacteria concentration (0.0 to 1.0)
  float toxicCompoundsLevel;    // Estimated toxic compounds level (0.0 to 1.0)
  char warnings[256];           // Human-readable warnings
};

class WaterQualityClassifier {
  public:
    WaterQualityClassifier();
    
    // Initialize the classifier and load ML model
    bool begin();
    
    // Classify water quality from sensor data
    ClassificationResult classifyWaterQuality(
      const OpticalData& opticalData,
      const SpectralData& spectralData
    );
    
    // Check if classifier is ready
    bool isReady();
    
    // Get model information
    const char* getModelVersion();
    
  private:
    bool initialized;
    char modelVersion[32];
    
    // Internal ML processing
    float analyzeBacteria(const OpticalData& opticalData);
    float analyzeToxicCompounds(const SpectralData& spectralData);
    void generateWarnings(ClassificationResult& result);
    
    // Feature extraction
    void extractOpticalFeatures(const OpticalData& opticalData, float* features, int numFeatures);
    void extractSpectralFeatures(const SpectralData& spectralData, float* features, int numFeatures);
    
    // Thresholds for classification
    const float BACTERIA_SAFE_THRESHOLD = 0.3;
    const float TOXIC_SAFE_THRESHOLD = 0.3;
    const float MIN_CONFIDENCE = 0.5;
};

#endif // WATER_QUALITY_CLASSIFIER_H
