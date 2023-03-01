#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "driver/ledc.h"

#define LEDC_GPIO 27
ledc_channel_config_t ledc_channel; // need static? calling init function from main then motor_task from main

void init_hw(void)
{
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
    ledc_channel.gpio_num = LEDC_GPIO;
    ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel.hpoint = 0;
    ledc_channel.timer_sel = LEDC_TIMER_0;
    ledc_channel_config(&ledc_channel);
}

void motor_task(void *pvParameter)
{
    while (1)
    {
        // duty range (2**duty_resolution) - 1
        //0 - 1023??
        ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, 255);
        ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
        vTaskDelay(2000 / portTICK_RATE_MS);
        ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, 120);
        ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
        vTaskDelay(2000 / portTICK_RATE_MS);
    }
}
