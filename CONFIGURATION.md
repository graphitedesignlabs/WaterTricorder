# Water Tricorder Configuration Guide

## Overview

This guide covers configuration options for the Water Tricorder firmware.

## System Configuration

### Power Management

Battery monitoring thresholds can be adjusted in `src/power/PowerManager.h`:

```cpp
const float BATTERY_LOW_THRESHOLD = 3.3;   // Volts - adjust based on battery type
const float BATTERY_MAX_VOLTAGE = 4.2;     // Volts - for Li-ion batteries
const unsigned long BATTERY_CHECK_INTERVAL = 60000; // Check every 60 seconds
```

### Sensor Configuration

#### Optical Sensor

Image capture parameters in `src/sensors/OpticalSensor.h`:

```cpp
// Image resolution (can be adjusted based on camera sensor)
#define IMAGE_WIDTH 128
#define IMAGE_HEIGHT 128
```

Future configuration options:
- Magnification level
- Focus distance
- Lighting intensity
- Exposure time

#### Spectrometer

Spectral range configuration in `src/sensors/Spectrometer.h`:

```cpp
#define SPECTRAL_BANDS 64  // Number of wavelength bands to measure
```

In `src/sensors/Spectrometer.cpp`:
```cpp
float startWavelength = 380.0;  // Starting wavelength (nm)
float endWavelength = 750.0;    // Ending wavelength (nm)
```

### ML Classifier Configuration

Safety thresholds in `src/ml/WaterQualityClassifier.h`:

```cpp
const float BACTERIA_SAFE_THRESHOLD = 0.3;    // Adjust based on calibration
const float TOXIC_SAFE_THRESHOLD = 0.3;       // Adjust based on calibration
const float MIN_CONFIDENCE = 0.5;             // Minimum confidence for results
```

**Important**: These thresholds should be calibrated with actual water samples and laboratory analysis before deployment.

## Display Configuration

### Result Display Duration

In `WaterTricorder.ino`:

```cpp
if (millis() - displayStartTime > 30000) { // Display results for 30 seconds
```

Adjust this value to change how long results are displayed before returning to idle mode.

## Serial Debugging

To enable/disable debug output, modify the Serial.println() statements throughout the code, or implement a global DEBUG flag:

```cpp
#define DEBUG_MODE true  // Add to top of WaterTricorder.ino

// Then conditionally print:
#if DEBUG_MODE
  Serial.println("Debug message");
#endif
```

## Hardware Pin Configuration

### GPIO Pin Assignments

To be configured based on actual hardware design:

```cpp
// Example pin definitions (add to appropriate files)
#define OPTICAL_SENSOR_PIN A0
#define SPECTROMETER_PIN A1
#define BUTTON_PIN D2
#define BATTERY_VOLTAGE_PIN A7
#define DISPLAY_SDA_PIN D4
#define DISPLAY_SCL_PIN D5
```

### I2C Configuration

For sensors and display using I2C:

```cpp
#define I2C_SPEED 400000  // 400kHz fast mode
```

## Calibration

### Sensor Calibration

Before first use and periodically:

1. **Optical Sensor Calibration**
   - Use distilled water as baseline
   - Adjust brightness/contrast normalization
   - Verify focus at correct magnification

2. **Spectrometer Calibration**
   - Use known reference spectrum (e.g., fluorescent light)
   - Calibrate wavelength mapping
   - Measure dark current baseline

### ML Model Configuration

The ML model needs to be trained with your specific hardware:

1. Collect training data with your sensors
2. Label data with laboratory analysis results
3. Train TensorFlow model
4. Convert to TensorFlow Lite format
5. Deploy to device
6. Adjust thresholds based on validation results

## Performance Tuning

### Sampling Rate

Adjust timing in the main loop:

```cpp
delay(10); // Main loop delay - reduce for faster response
```

### Power Optimization

- Adjust sleep durations in `handleLowPowerState()`
- Configure sensor power-down intervals
- Optimize display refresh rates

## Safety Considerations

**CRITICAL**: This device is currently in development. The ML models and thresholds are not calibrated for real-world use.

**DO NOT** rely on this device for drinking water decisions until:
1. Sensors are properly calibrated with laboratory-grade equipment
2. ML models are trained on extensive validated datasets
3. Device accuracy is verified against certified water testing methods
4. Appropriate safety margins are established

## Testing Configuration

For development and testing without hardware:

The current implementation uses simulated sensor data. This can be configured in:
- `OpticalSensor::captureImage()` - generates random test images
- `Spectrometer::captureSpectrum()` - generates synthetic spectra

Replace these with actual hardware interfaces as development progresses.

## Advanced Configuration

### TensorFlow Lite Model

To load a custom TensorFlow Lite model:

1. Convert your trained model to TensorFlow Lite format
2. Generate C array representation
3. Include in `src/ml/WaterQualityClassifier.cpp`
4. Update model initialization code

### Custom Sensors

To add additional sensors:

1. Create new sensor class in `src/sensors/`
2. Include in main sketch
3. Integrate data into ML classifier
4. Update result structure if needed

## Configuration Best Practices

1. **Version Control**: Track configuration changes in git
2. **Documentation**: Document any threshold adjustments and their rationale
3. **Calibration Records**: Keep records of calibration data and dates
4. **Testing**: Always test configuration changes with known samples
5. **Safety First**: Err on the side of caution with safety thresholds

## Support

For questions about configuration, please contact the development team or open an issue on the GitHub repository.
