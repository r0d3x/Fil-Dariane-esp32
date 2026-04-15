#ifndef CONFIG_H
#define CONFIG_H

// ---- QTR-8 sensor pins ----
#define S1_PIN 32
#define S2_PIN 33
#define S3_PIN 25
#define S4_PIN 26
#define S5_PIN 27
#define S6_PIN 14
#define S7_PIN 12
#define S8_PIN 13

// ---- TB6612FNG motor driver pins ----
#define PWMA_PIN 5
#define AIN1_PIN 18
#define AIN2_PIN 19
#define PWMB_PIN 21
#define BIN1_PIN 22
#define BIN2_PIN 23

// Note: STBY is hardwired to 3.3V so it's always enabled

// ---- pwm settings ----
#define PWM_FREQ 5000
#define PWM_RES  8 // 8-bit resolution (0-255 range)
#define MOT_A_CH 0
#define MOT_B_CH 1

// ---- globals ----
extern float Kp;
extern float Ki;
extern float Kd;
extern int baseSpeed;

#endif
