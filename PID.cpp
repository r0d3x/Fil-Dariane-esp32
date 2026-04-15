#include "PID.h"

PIDController pid;

void PIDController::begin() {
    lastTime = micros();
}

void PIDController::compute(float error) {
    unsigned long now = micros();
    float dt = (now - lastTime) / 1000000.0f; // dt in seconds
    
    // avoid division by zero or weirdly long delays
    if (dt <= 0.0f || dt > 1.0f) {
        dt = 0.010f; // fallback to 10ms
    }

    integral += error * dt;

    // anti-windup to keep the integral term in check
    if (integral > 100.0f) integral = 100.0f;
    else if (integral < -100.0f) integral = -100.0f;

    float derivative = (error - lastError) / dt;
    
    // crunch the numbers
    float output = (Kp * error) + (Ki * integral) + (Kd * derivative);

    // save current state for next run
    lastError = error;
    lastTime = now;

    // apply our steering value to the motors
    // positive output = turn right (speed up left motor, slow down right motor)
    int speedMotorA = baseSpeed + (int)output; // left
    int speedMotorB = baseSpeed - (int)output; // right

    motors.setSpeeds(speedMotorA, speedMotorB);
}
