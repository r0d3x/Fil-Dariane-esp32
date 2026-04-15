#include <Arduino.h>
#include "Config.h"
#include "Motors.h"
#include "Sensors.h"
#include "Bluetooth.h"
#include "PID.h"

// globals
float Kp = 10.0;
float Ki = 0.0;
float Kd = 1.0;
int baseSpeed = 150;

unsigned long lastLoopTime = 0;
const unsigned long LOOP_DELAY_US = 10000; // run loop at ~100Hz (10ms)

void setup() {
    Serial.begin(115200);
    
    // init hardware
    motors.begin();
    sensors.begin();
    btCommand.begin();
    pid.begin();

    // start calibration
    // give some time to put the robot on the line
    Serial.println("Place the robot on the line. Calibration starts in 2 seconds...");
    delay(2000);
    
    Serial.println("Starting Calibration (sweep sensors over black and white)...");
    unsigned long startTime = millis();
    
    // sweep sensors back and forth across the line for 5 secs to find max/min values
    while (millis() - startTime < 5000) {
        sensors.calibrate();
        delay(5);
    }
    Serial.println("Calibration complete.");

    // quick pause before taking off
    delay(1000); 
    lastLoopTime = micros();
}

void loop() {
    unsigned long now = micros();
    
    // throttle the control loop to keep it steady (100Hz)
    if (now - lastLoopTime >= LOOP_DELAY_US) {
        lastLoopTime = now;

        // check for BT commands without blocking the loop
        btCommand.processCommands();

        // get position error: -3.5 (left) to 3.5 (right), 0 is dead center
        float error = sensors.readPosition();

        // calculate PID and update motor speeds
        pid.compute(error);
    }
}
