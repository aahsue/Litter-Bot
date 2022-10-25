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

void app_main(void)
{
    start_gatt_server();
}
