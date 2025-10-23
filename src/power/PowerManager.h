/*
 * PowerManager.h
 * 
 * Power management for low-power operation.
 * Monitors battery level and manages sleep states.
 * 
 * Design goal: Minimal power consumption, solar-powered if possible
 */

#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include <Arduino.h>

class PowerManager {
  public:
    PowerManager();
    
    // Initialize power management
    bool begin();
    
    // Battery monitoring
    float getBatteryVoltage();
    float getBatteryPercentage();
    bool isBatteryLow();
    bool isBatteryCharging();
    
    // Power modes
    void sleep(unsigned long durationMs);
    void deepSleep(unsigned long durationMs);
    void wake();
    
    // Power consumption optimization
    void enableLowPowerMode();
    void disableLowPowerMode();
    bool isLowPowerMode();
    
    // System power control
    void powerOnSensors();
    void powerOffSensors();
    void powerOnDisplay();
    void powerOffDisplay();
    
  private:
    bool initialized;
    bool lowPowerMode;
    float lastBatteryVoltage;
    unsigned long lastBatteryCheck;
    
    // Constants
    const float BATTERY_LOW_THRESHOLD = 3.3;   // Volts
    const float BATTERY_MAX_VOLTAGE = 4.2;     // Volts (for Li-ion)
    const unsigned long BATTERY_CHECK_INTERVAL = 60000; // 1 minute
    
    // Internal functions
    void updateBatteryStatus();
    float readBatteryVoltage();
};

#endif // POWER_MANAGER_H
