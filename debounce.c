#include "debounce.h"

button_output_t handleButton(button_contents_t* self,
                             bool isPressed)
{
    if (self->timerCounter>=32767)
        self->timerCounter--;
    if (self->releaseCounter>=32767)
        self->releaseCounter--;
    if (isPressed)
    {

        ++self->timerCounter;
        if (self->timerCounter>=self->longPressTime)
        {
            self->timerCounter = 0;
            self->longPressDetected = true;
            self->wasPressedOnce = true;
        }
        if(self->longPressDetected)
            return BS_LONG_PRESSED;
        else if (self->timerCounter>=self->debouncingTime)
            self->wasPressedOnce = true;
        else
            return BS_BOUNCING;
    }
    else
    {
        if (self->wasPressedOnce && !self->longPressDetected)
        {
            self->releaseCounter++;
            if (self->releaseCounter>=self->doublePressGap)
            {
                self->releaseCounter = 0;
                self->wasPressedOnce = false;
                self->timerCounter = 0;
                return BS_PRESSED;
            }
            return BS_BOUNCING;
        }
        else
        {
            self->wasPressedOnce = false;
            self->longPressDetected = false;
            return BS_UNPRESSED;
        }

    }
}
