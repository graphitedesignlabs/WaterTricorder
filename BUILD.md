# Building and Uploading the Water Tricorder Firmware

## Hardware Requirements

- **Arduino Nano 33 BLE Sense** (or compatible board)
- USB cable for programming
- Optional: Custom PCB with sensors (optical sensor and spectrometer)

## Software Requirements

### Arduino IDE

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software) (version 1.8.13 or later)
2. Install the Arduino SAMD Boards package:
   - Open Arduino IDE
   - Go to Tools → Board → Boards Manager
   - Search for "Arduino SAMD Boards (32-bits ARM Cortex-M0+)"
   - Install the package

3. Install the Arduino Nano 33 BLE board support:
   - Go to Tools → Board → Boards Manager
   - Search for "Arduino Mbed OS Nano Boards"
   - Install the package

### Required Libraries

Install the following libraries via Arduino IDE Library Manager (Sketch → Include Library → Manage Libraries):

1. **TensorFlow Lite for Microcontrollers**
   - Search for "Arduino_TensorFlowLite"
   - Install the latest version

2. **Additional libraries** (to be added as hardware is integrated):
   - Camera/sensor libraries
   - Display libraries (e.g., Adafruit_SSD1306 for OLED)
   - Any sensor-specific libraries

## Building the Project

### Using Arduino IDE

1. Open `WaterTricorder.ino` in Arduino IDE
2. Select the correct board:
   - Go to Tools → Board → Arduino Mbed OS Nano Boards → Arduino Nano 33 BLE
3. Select the correct port:
   - Go to Tools → Port → Select the COM port for your device
4. Verify/compile the sketch:
   - Click the checkmark button or go to Sketch → Verify/Compile
5. Upload to the board:
   - Click the arrow button or go to Sketch → Upload

### Using Arduino CLI (Advanced)

```bash
# Install Arduino CLI
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

# Install core and libraries
arduino-cli core install arduino:mbed_nano
arduino-cli lib install Arduino_TensorFlowLite

# Compile
arduino-cli compile --fqbn arduino:mbed_nano:nano33ble WaterTricorder.ino

# Upload
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:mbed_nano:nano33ble WaterTricorder.ino
```

## Project Structure

```
WaterTricorder/
├── WaterTricorder.ino          # Main Arduino sketch
├── src/
│   ├── sensors/
│   │   ├── OpticalSensor.h     # Optical microscopy sensor
│   │   ├── OpticalSensor.cpp
│   │   ├── Spectrometer.h      # Spectrometer sensor
│   │   └── Spectrometer.cpp
│   ├── ml/
│   │   ├── WaterQualityClassifier.h    # ML classifier
│   │   └── WaterQualityClassifier.cpp
│   ├── ui/
│   │   ├── Display.h           # Display management
│   │   └── Display.cpp
│   └── power/
│       ├── PowerManager.h      # Power management
│       └── PowerManager.cpp
├── BUILD.md                    # This file
├── CONFIGURATION.md            # Configuration guide
└── README.md                   # Project overview
```

## Testing

### Serial Monitor

After uploading, open the Serial Monitor (Tools → Serial Monitor) at 115200 baud to view debug output and system status.

### Initial Test

The current implementation includes stub functions that simulate sensor readings. This allows you to test the software flow before actual hardware is connected.

## Troubleshooting

### Upload Fails

- Ensure the correct board and port are selected
- Try pressing the reset button on the board twice quickly to enter bootloader mode
- Check USB cable and connection

### Compilation Errors

- Verify all required libraries are installed
- Check that board support packages are up to date
- Ensure file paths are correct

### Serial Output Issues

- Verify baud rate is set to 115200
- Try resetting the board after upload
- Check that Serial Monitor is connected to the correct port

## Next Steps

1. Integrate actual sensor hardware
2. Implement real sensor reading code
3. Train and integrate TensorFlow Lite models
4. Add display hardware support
5. Calibrate sensors
6. Test with real water samples

## Contributing

See the main README.md for information on contributing to this project.
