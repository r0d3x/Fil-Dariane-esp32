#ifndef PID_H
#define PID_H

#include <Arduino.h>
#include "Config.h"
#include "Motors.h"

class PIDController {
private:
    float lastError = 0;
    float integral = 0;
    unsigned long lastTime = 0;

public:
    void begin();
    void compute(float currentError);
};

extern PIDController pid;

#endif
