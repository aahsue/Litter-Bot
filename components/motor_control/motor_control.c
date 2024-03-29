#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "motor_control.h"

// motor A = left, motor B = right
#define MR_FWD_PIN 33
#define MR_BACK_PIN 25
#define ML_FWD_PIN 26
#define ML_BACK_PIN 18
#define ML_SPD_PIN 2
#define MR_SPD_PIN 4
static ledc_channel_config_t ledc_channel;

void init_hw(void);
bool set_motor_pwm(motor_t motor, uint16_t dc);
bool set_motor_dir(motor_t motor, motor_dir_t dir);
void motor_task(void *pvParameter);

void init_hw(void)
{
    gpio_set_direction(MR_FWD_PIN, GPIO_MODE_OUTPUT); 
    gpio_set_direction(MR_BACK_PIN, GPIO_MODE_OUTPUT); 
    gpio_set_direction(ML_BACK_PIN, GPIO_MODE_OUTPUT); 
    gpio_set_direction(ML_FWD_PIN, GPIO_MODE_OUTPUT); 

    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 1000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    ledc_timer_config(&ledc_timer);
    ledc_channel.channel = LEDC_CHANNEL_0;
    ledc_channel.duty = 0;
    ledc_channel.gpio_num = ML_SPD_PIN;
    ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel.hpoint = 0;
    ledc_channel.timer_sel = LEDC_TIMER_0;
    ledc_channel_config(&ledc_channel);

    ledc_channel.channel = LEDC_CHANNEL_1;
    ledc_channel.duty = 0;
    ledc_channel.gpio_num = MR_SPD_PIN;
    ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel.hpoint = 0;
    ledc_channel.timer_sel = LEDC_TIMER_0;
    ledc_channel_config(&ledc_channel);
}

//dc should be 0 to 1023????
bool set_motor_pwm(motor_t motor, uint16_t dc) {
    ledc_channel_t motor_pwm_channel = LEDC_CHANNEL_0;
    switch(motor) {
        case MOTOR_LEFT:
            motor_pwm_channel = LEDC_CHANNEL_0;
            break;
        case MOTOR_RIGHT:
            motor_pwm_channel = LEDC_CHANNEL_1;
            break;
    }

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, motor_pwm_channel, dc);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, motor_pwm_channel);
    return true;
}

bool set_motor_dir(motor_t motor, motor_dir_t dir) {
    uint32_t fwd_pin_state = 0;
    uint32_t back_pin_state = 0;
    
    switch(dir) {
        case DIR_FORWARD:
            fwd_pin_state = 1;
            back_pin_state = 0;
            break;
        case DIR_BACKWARD:
            fwd_pin_state = 0;
            back_pin_state = 1;
            break;
        case DIR_STOP_HARD:
            /* TODO: Verify diff between HARD and SOFT stopping */
            fwd_pin_state = 0;
            back_pin_state = 0;
            break;
        case DIR_STOP_SOFT: // coasting
            /* TODO: Implement */
            fwd_pin_state = 0;
            back_pin_state = 0;
            break;
        default:
            break;
         /*TODO: Handle*/

    }

    gpio_num_t fwd_pin = 0;
    gpio_num_t back_pin = 0;
    
    switch(motor) {
        case MOTOR_LEFT:
            fwd_pin   = ML_FWD_PIN;
            back_pin  = ML_BACK_PIN;
            break;
        case MOTOR_RIGHT:
            fwd_pin   = MR_FWD_PIN;
            back_pin  = MR_BACK_PIN;
            break;
        default:
            break;
            /* TODO: Handle */

    }

    gpio_set_level(fwd_pin, fwd_pin_state);
    gpio_set_level(back_pin, back_pin_state);

    return true;
}