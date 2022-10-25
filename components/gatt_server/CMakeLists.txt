idf_component_register(SRCS "gatt_server.c"
                       INCLUDE_DIRS "."
                                    "../../main"
                       REQUIRES nvs_flash bt)