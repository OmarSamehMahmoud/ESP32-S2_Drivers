set(SRC_FILES
    main.c
    middleware.c
    MCAL/GPIO/MCAL_ESP32_S2_SOLO_2_N4R2_GPIO.c
)

idf_component_register(SRCS ${SRC_FILES}
                    INCLUDE_DIRS ".")
