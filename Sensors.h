#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "Config.h"

#define NUM_SENSORS 8

class Sensors {
private:
    int sensorPins[NUM_SENSORS] = {S1_PIN, S2_PIN, S3_PIN, S4_PIN, S5_PIN, S6_PIN, S7_PIN, S8_PIN};
    int calMin[NUM_SENSORS];
    int calMax[NUM_SENSORS];
    float lastPosition = 0;

public:
    void begin();
    void resetCalibration();
    void calibrate();
    void readCalibrated(int* sensorValues);
    float readPosition();
};

extern Sensors sensors;

#endif
