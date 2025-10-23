# Development Guide

## For Developers

This guide is for developers who want to contribute to or modify the Water Tricorder firmware.

## Architecture Overview

The Water Tricorder firmware follows a modular architecture:

```
Main Application (State Machine)
    ↓
┌───────────┬─────────────┬──────────┬────────────┐
│  Sensors  │  ML/AI      │  UI      │   Power    │
├───────────┼─────────────┼──────────┼────────────┤
│ Optical   │ Classifier  │ Display  │ Battery    │
│ Spectro   │ TF Lite     │ Buttons  │ Sleep      │
└───────────┴─────────────┴──────────┴────────────┘
```

## Code Organization

### Main Application (`WaterTricorder.ino`)

The main sketch implements a state machine with the following states:
- `STATE_IDLE`: Waiting for user to start test
- `STATE_SAMPLING`: Collecting data from sensors
- `STATE_ANALYZING`: Running ML inference
- `STATE_DISPLAYING_RESULTS`: Showing results to user
- `STATE_LOW_POWER`: Battery-saving mode

### Sensor Layer (`src/sensors/`)

Each sensor class follows a consistent interface:
```cpp
bool begin();           // Initialize hardware
bool capture*();        // Capture data
*Data getLastReading(); // Get last captured data
bool isReady();         // Check if sensor is operational
void sleep() / wake();  // Power management
```

#### OpticalSensor
- Interfaces with microscope camera
- Captures grayscale images (default 128x128)
- Calculates basic image statistics
- Future: Add image preprocessing for ML

#### Spectrometer
- Measures light intensity across wavelength bands
- Default: 64 bands from 380nm to 750nm (UV to red)
- Identifies peak wavelengths
- Future: Add baseline subtraction, calibration

### Machine Learning (`src/ml/`)

#### WaterQualityClassifier
- Analyzes sensor data to determine water potability
- Currently uses simple heuristics (stub for ML model)
- Future: Integrate actual TensorFlow Lite model

**To add a trained model:**
1. Train model using TensorFlow
2. Convert to TensorFlow Lite (.tflite)
3. Convert to C array: `xxd -i model.tflite > model_data.cpp`
4. Include in classifier
5. Update inference code

### User Interface (`src/ui/`)

#### Display
- Manages all screen output
- Currently outputs to Serial (for development)
- Future: Add OLED/LCD driver support

**To add display hardware:**
1. Include appropriate library (e.g., Adafruit_SSD1306)
2. Initialize in `Display::begin()`
3. Implement actual drawing in show* methods
4. Update button handling for real GPIO

### Power Management (`src/power/`)

#### PowerManager
- Monitors battery voltage
- Controls sleep modes
- Manages power to subsystems

**Power optimization tips:**
- Use sleep() during idle periods
- Power down sensors when not in use
- Reduce display brightness when possible
- Consider deep sleep for extended idle

## Development Workflow

### 1. Setting Up Development Environment

```bash
# Install Arduino CLI
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

# Install required packages
arduino-cli core install arduino:mbed_nano
arduino-cli lib install Arduino_TensorFlowLite

# Clone repository
git clone https://github.com/graphitedesignlabs/WaterTricorder.git
cd WaterTricorder
```

### 2. Making Changes

1. Create a feature branch
2. Make targeted changes to relevant modules
3. Test with example sketches
4. Update documentation if needed

### 3. Testing

#### Without Hardware (Simulation)
The current stub implementations allow testing the control flow:
```bash
arduino-cli compile --fqbn arduino:mbed_nano:nano33ble WaterTricorder.ino
```

#### With Hardware
1. Connect Arduino Nano 33 BLE
2. Upload firmware
3. Open Serial Monitor (115200 baud)
4. Observe debug output
5. Test with actual sensors

#### Unit Testing
Currently not implemented. Future: Add unit tests for:
- Sensor data processing
- ML feature extraction
- Classification logic
- State machine transitions

### 4. Debugging

**Serial Output:**
All modules output debug information via Serial. Monitor at 115200 baud.

**Common Issues:**
- Sensor initialization fails: Check hardware connections
- Classification confidence low: Calibrate thresholds
- Display not updating: Check timing in update loop
- Battery reading incorrect: Verify voltage divider values

## Adding New Features

### Adding a New Sensor

1. Create header file: `src/sensors/NewSensor.h`
2. Define data structure and interface
3. Implement in `src/sensors/NewSensor.cpp`
4. Include in main sketch
5. Add to sampling state
6. Integrate data into classifier

### Modifying ML Classifier

1. Collect training data from sensors
2. Label data with laboratory results
3. Train model in Python/TensorFlow
4. Convert to TensorFlow Lite
5. Update `WaterQualityClassifier` to load model
6. Adjust thresholds based on validation

### Extending the State Machine

1. Add new state to enum in `WaterTricorder.ino`
2. Implement handler function
3. Add transitions from existing states
4. Update display for new state

## Code Style Guidelines

- Use descriptive variable names
- Comment complex logic
- Keep functions focused and small
- Use consistent indentation (2 spaces)
- Add debug Serial.println() for new features
- Mark hardware TODOs clearly

## Testing Checklist

Before submitting changes:
- [ ] Code compiles without warnings
- [ ] Serial output is informative
- [ ] State machine transitions work correctly
- [ ] Sensor data is validated
- [ ] Power management functions as expected
- [ ] Documentation is updated
- [ ] Safety warnings are preserved

## ML Model Development

### Data Collection
1. Capture sensor data from water samples
2. Get laboratory analysis for each sample
3. Store data with proper labels
4. Create training/validation/test splits

### Model Training
```python
# Example TensorFlow training pipeline
import tensorflow as tf

# Load and preprocess data
train_data = load_sensor_data('train/')
train_labels = load_labels('train/')

# Define model
model = tf.keras.Sequential([
    tf.keras.layers.Dense(64, activation='relu'),
    tf.keras.layers.Dense(32, activation='relu'),
    tf.keras.layers.Dense(2, activation='softmax')  # Binary: safe/unsafe
])

# Train
model.compile(optimizer='adam', 
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])
model.fit(train_data, train_labels, epochs=50)

# Convert to TensorFlow Lite
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()
open('water_quality_model.tflite', 'wb').write(tflite_model)
```

### Model Deployment
1. Convert .tflite to C array
2. Include in firmware
3. Update model loading code
4. Verify inference performance

## Hardware Integration Notes

### Pin Assignments
Document all GPIO pin assignments in one place:
```cpp
// sensors/config.h
#define OPTICAL_SENSOR_PIN A0
#define SPECTROMETER_LED_PIN D3
// etc.
```

### I2C Devices
Keep track of I2C addresses to avoid conflicts:
```cpp
#define DISPLAY_I2C_ADDR 0x3C
#define SENSOR_I2C_ADDR 0x29
```

### Power Budget
Track current consumption of all components:
- Arduino Nano 33 BLE: ~7mA (idle), ~20mA (active)
- Optical sensor: TBD
- Spectrometer: TBD
- Display: ~15mA (OLED)
- Total budget: < 100mA for USB power

## Safety and Validation

### Critical Thresholds
All safety thresholds must be:
1. Calibrated against certified standards
2. Validated with extensive testing
3. Set with appropriate safety margins
4. Documented with justification

### Testing Requirements
Before field deployment:
1. Test with certified reference samples
2. Compare results with laboratory analysis
3. Validate across range of conditions
4. Document accuracy and limitations

## Contributing

1. Fork the repository
2. Create feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open Pull Request

## Resources

- [Arduino Nano 33 BLE Documentation](https://docs.arduino.cc/hardware/nano-33-ble)
- [TensorFlow Lite for Microcontrollers](https://www.tensorflow.org/lite/microcontrollers)
- [Public Lab Spectrometry](https://publiclab.org/wiki/spectrometry)
- [Water Quality Standards](https://www.epa.gov/ground-water-and-drinking-water)

## Support

- Open an issue for bugs or feature requests
- Join the discussion in issues
- Contact: hello@graphitedesignlabs.com

## License

See LICENSE.txt
