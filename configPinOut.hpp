#pragma once

// Declarations

void pinModeConfig ();

// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

// Inputs: all except 6 to 11 that are connected to SPI Flash
// From 34 to 39 can not generate PWM
// 36 29 34 35 Input only

#define ENCODER_LEFT_A 27
#define ENCODER_LEFT_B 26

#define ENCODER_RIGHT_A 35
#define ENCODER_RIGHT_B 34

#define ENABLE_MOTOR_CONTROL 33

#define FORDWARD_LEFT 19
#define BACKWARD_LEFT 18 
#define PWM_LEFT 5

#define FORDWARD_RIGHT 25
#define BACKWARD_RIGHT 14
#define PWM_RIGHT 13

#define RADIO_DIR 2
#define RADIO_VEL 4

// I2C

#define I2C_SDA 21
#define I2C_SCL 22

// IMU

#define INTERRUPT_PIN 15



