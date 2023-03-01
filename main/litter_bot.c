/****************************************************************************
*
* litter_bot.c
* Contains app_main. Starts Gatt Server and advertises for connection.
*
****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "gatt_server.h"
#include "motor_control.h"

static const uint32_t stack_depth = 4096; // decide on this size or configMINIMAL_STACK_SIZE

void app_main(void)
{
    /** Initialization **/
    init_hw();
    init_gatt_server(); // also starts GATT server because GATT server is asynchronous and relies on callbacks

    /** Multitasking **/
    xTaskCreate(&motor_task,
                "motor_task",
                stack_depth,
                NULL,
                1,
                NULL); // figure this outttt do i need smthn
}

