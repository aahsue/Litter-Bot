#ifndef MOTOR_CONTROL__H
#define MOTOR_CONTROL__H

#include "driver/ledc.h"

typedef enum {
	MOTOR_LEFT,
	MOTOR_RIGHT
} motor_t;

typedef enum {
	DIR_FORWARD,
	DIR_BACKWARD,
	DIR_STOP_HARD,
	DIR_STOP_SOFT
} motor_dir_t;

void init_hw(void);
bool set_motor_pwm(motor_t motor, uint16_t dc);
bool set_motor_dir(motor_t motor, motor_dir_t dir);

#endif