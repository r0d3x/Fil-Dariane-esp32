#include "Sensors.h"

Sensors sensors;

void Sensors::begin() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        pinMode(sensorPins[i], INPUT);
    }
    resetCalibration();
}

void Sensors::resetCalibration() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        calMin[i] = 4095; // default 12-bit max for esp32
        calMax[i] = 0;
    }
}

// call this in a fast loop while manually swinging the bot over the line
void Sensors::calibrate() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        int val = analogRead(sensorPins[i]);
        if (val < calMin[i]) calMin[i] = val;
        if (val > calMax[i]) calMax[i] = val;
    }
}

// get calibrated values and map to 0-1000
void Sensors::readCalibrated(int* sensorValues) {
    for (int i = 0; i < NUM_SENSORS; i++) {
        int val = analogRead(sensorPins[i]);
        val = constrain(val, calMin[i], calMax[i]);
        
        // map to 0-1000. standard logic assumes higher read = more reflective
        // (if your hardware does the opposite, map to 1000 -> 0 instead)
        if (calMax[i] == calMin[i]) {
            sensorValues[i] = 0;
        } else {
            sensorValues[i] = map(val, calMin[i], calMax[i], 0, 1000);
        }
    }
}

// calculate center of mass to figure out where the line is
// returns -3.5 (far left) to +3.5 (far right)
float Sensors::readPosition() {
    int sensorValues[NUM_SENSORS];
    readCalibrated(sensorValues);

    long sum = 0;
    float weightedSum = 0;

    for (int i = 0; i < NUM_SENSORS; i++) {
        int val = sensorValues[i];
        sum += val;
        // weight sensors from left (-3.5) to right (+3.5)
        float weight = (i - 3.5f);
        weightedSum += (val * weight);
    }

    if (sum < 200) { // lost the line? (also filters out noise)
        // just remember the last side we saw it on and steer hard that way
        if (lastPosition > 0) return 3.5f;
        else return -3.5f;
    }

    lastPosition = weightedSum / sum;
    return lastPosition;
}
