/*
==========================================
              Button Debounce Module
==========================================
 * debounce.h
 *
 * A module for handling button debouncing,
 * long-press, and double-press detection.
 *
 * Author: Mohamed Abdelmoneim
 * Date: 10/15/2024
 */

#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    BS_PRESSED,
    BS_BOUNCING,
    BS_UNPRESSED,
    BS_LONG_PRESSED
} button_output_t;


typedef struct
{
    uint16_t    debouncingTime;
    uint16_t    timerCounter;
    uint16_t    longPressTime;
} button_contents_t;


button_output_t handleButton(button_contents_t* self,
                  bool isPressed);

#endif
