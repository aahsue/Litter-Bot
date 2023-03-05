idf_component_register(SRCS "gatt_server.c"
                       INCLUDE_DIRS "."
                                    "../../main"
                                    "../motor_control"
                       REQUIRES nvs_flash bt)