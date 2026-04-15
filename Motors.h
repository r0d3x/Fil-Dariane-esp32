#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include "Config.h"

class Motors {
public:
    void begin();
    void setSpeeds(int speedLeft, int speedRight);
    void setMotorA(int speed);
    void setMotorB(int speed);
};

extern Motors motors;

#endif
