Water Tricorder
===============

Approximately 2 billion people around the world are affected by poor water
quality.

This is a low cost opensource device for quickly and reliably answering the question: "can I drink this water?" It uses spectrometry for measuring toxic inorganic compounds and microscopy for sensing concentrations of harmful microorganisms. Both systems coordinate with on-device machine learning for instant readings. 

## Status

**Development Phase**: Initial code structure implemented based on design notes.

⚠️ **Warning**: This device is currently in early development. Do not use for actual water quality assessment until sensors are calibrated and ML models are trained with validated data.

## Hardware

- **CPU**: Arduino Nano 33 BLE Sense
- **Optical Sensor**: Portable microscope (design in progress)
- **Spectrometer**: Based on Public Lab's DIY spectrometer design
- **ML**: TensorFlow Lite for Microcontrollers
- **Power**: Low-power design for battery or solar operation

## Quick Start

1. See [BUILD.md](BUILD.md) for instructions on building and uploading the firmware
2. See [CONFIGURATION.md](CONFIGURATION.md) for configuration options
3. Read the [design notes](DESIGN-NOTES.md) for project goals and principles

## Project Structure

```
WaterTricorder/
├── WaterTricorder.ino          # Main Arduino sketch
├── src/
│   ├── sensors/                # Sensor interface implementations
│   ├── ml/                     # Machine learning classifier
│   ├── ui/                     # Display management
│   └── power/                  # Power management
├── examples/                   # Example sketches
├── BUILD.md                    # Build instructions
├── CONFIGURATION.md            # Configuration guide
├── DESIGN-NOTES.md            # Design principles and goals
└── README.md                   # This file
```

## Features

- **Dual Sensing**: Optical microscopy for microorganisms + spectrometry for toxic compounds
- **On-Device ML**: TensorFlow Lite classifier runs directly on the microcontroller
- **Low Power**: Optimized for minimal power consumption with sleep modes
- **Simple Interface**: One-button operation with clear safe/unsafe indicator
- **Modular Design**: Easy to extend and customize for different use cases

## Current Implementation

The current codebase provides:
- Complete software architecture for water quality assessment
- Modular sensor interfaces ready for hardware integration
- ML classifier framework (needs trained model)
- Power management for low-power operation
- Display system for user interface
- Example test code

## Next Steps

1. ✅ Create initial code structure based on DESIGN-NOTES.md
2. ⬜ Integrate actual sensor hardware
3. ⬜ Implement camera/microscope interface
4. ⬜ Build/integrate spectrometer hardware
5. ⬜ Collect training data
6. ⬜ Train TensorFlow Lite models
7. ⬜ Calibrate sensors against laboratory standards
8. ⬜ Add display hardware support
9. ⬜ Field testing with real water samples
10. ⬜ Safety validation and certification

## Contributing

This is an open source project. Contributions are welcome!

Areas where help is needed:
- Hardware design for optical sensor and spectrometer
- Machine learning model development
- Field testing and calibration
- Documentation and tutorials
- Enclosure design

Read the [design notes](DESIGN-NOTES.md) and [join the project](mailto:hello@graphitedesignlabs.com).

## License

See [LICENSE.txt](LICENSE.txt) for details.

## Safety Notice

**IMPORTANT**: This device is in development and has not been validated for actual use. Do not rely on it for drinking water decisions. Always use certified water testing methods when safety is critical.
