/*
 * Display.h
 * 
 * User interface display management.
 * Handles screen output and user interaction.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

// Forward declaration to avoid circular dependency
struct WaterQualityResult;

class Display {
  public:
    Display();
    
    // Initialize the display
    bool begin();
    
    // Display various screens
    void showSplashScreen();
    void showIdleScreen();
    void showSamplingScreen();
    void showAnalyzingScreen();
    void showResults(const WaterQualityResult& result);
    void showError(const char* message);
    void showLowPowerWarning();
    
    // Check for user input
    bool isTestButtonPressed();
    
    // Power management
    void sleep();
    void wake();
    
    // Update display content
    void update();
    
  private:
    bool initialized;
    bool inSleepMode;
    unsigned long lastUpdateTime;
    
    // Helper functions
    void clearScreen();
    void printCentered(const char* text, int line);
    void drawProgressBar(int progress);
    void drawPotabilityIndicator(bool isPotable, float confidence);
};

#endif // DISPLAY_H
