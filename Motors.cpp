#include "Motors.h"

Motors motors;

void Motors::begin() {
    pinMode(AIN1_PIN, OUTPUT);
    pinMode(AIN2_PIN, OUTPUT);
    pinMode(BIN1_PIN, OUTPUT);
    pinMode(BIN2_PIN, OUTPUT);

#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
    // For ESP32 core v3.x+
    ledcAttach(PWMA_PIN, PWM_FREQ, PWM_RES);
    ledcAttach(PWMB_PIN, PWM_FREQ, PWM_RES);
#else
    // For ESP32 core v2.x
    ledcSetup(MOT_A_CH, PWM_FREQ, PWM_RES);
    ledcAttachPin(PWMA_PIN, MOT_A_CH);
    
    ledcSetup(MOT_B_CH, PWM_FREQ, PWM_RES);
    ledcAttachPin(PWMB_PIN, MOT_B_CH);
#endif
}

// clamp speed to valid pwm range
int constrainSpeed(int speed) {
    if (speed > 255) return 255;
    if (speed < -255) return -255;
    return speed;
}

void Motors::setMotorA(int speed) { // left motor (assuming A is left)
    speed = constrainSpeed(speed);
    
    if (speed > 0) {
        digitalWrite(AIN1_PIN, HIGH);
        digitalWrite(AIN2_PIN, LOW);
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
        ledcWrite(PWMA_PIN, speed);
#else
        ledcWrite(MOT_A_CH, speed);
#endif
    } else if (speed < 0) {
        digitalWrite(AIN1_PIN, LOW);
        digitalWrite(AIN2_PIN, HIGH);
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
        ledcWrite(PWMA_PIN, -speed);
#else
        ledcWrite(MOT_A_CH, -speed);
#endif
    } else {
        digitalWrite(AIN1_PIN, LOW);
        digitalWrite(AIN2_PIN, LOW);
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
        ledcWrite(PWMA_PIN, 0);
#else
        ledcWrite(MOT_A_CH, 0);
#endif
    }
}

void Motors::setMotorB(int speed) { // right motor (assuming B is right)
    speed = constrainSpeed(speed);
    
    if (speed > 0) {
        digitalWrite(BIN1_PIN, HIGH); // swap these if the motor spins backwards
        digitalWrite(BIN2_PIN, LOW);
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
        ledcWrite(PWMB_PIN, speed);
#else
        ledcWrite(MOT_B_CH, speed);
#endif
    } else if (speed < 0) {
        digitalWrite(BIN1_PIN, LOW);
        digitalWrite(BIN2_PIN, HIGH);
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
        ledcWrite(PWMB_PIN, -speed);
#else
        ledcWrite(MOT_B_CH, -speed);
#endif
    } else {
        digitalWrite(BIN1_PIN, LOW);
        digitalWrite(BIN2_PIN, LOW);
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
        ledcWrite(PWMB_PIN, 0);
#else
        ledcWrite(MOT_B_CH, 0);
#endif
    }
}

void Motors::setSpeeds(int speedLeft, int speedRight) {
    setMotorA(speedLeft);
    setMotorB(speedRight);
}
