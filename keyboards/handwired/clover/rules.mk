SERIAL_DRIVER = vendor
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = rp2040_flash
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3360
OLED_ENABLE = yes
COMBO_ENABLE = yes
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
VPATH += keyboards/gboards
SRC += features/repeat_key.c
