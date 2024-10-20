#include "debounce.h"

button_output_t handleButton(button_contents_t* self,
                             bool isPressed)
{
    if (isPressed)
    {
        ++self->timerCounter;
        if (self->timerCounter>=self->longPressTime)
        {
            self->timerCounter = 0;
            self->wasPressedOnce = true;
            return BS_LONG_PRESSED;
        }
        return BS_BOUNCING;
    }
    else
    {
        if (self->timerCounter>=self->debouncingTime)
        {
            self->timerCounter = 0;
            self->wasPressedOnce = true;
            return BS_PRESSED;
        }
        else
            if (self->wasPressedOnce)
            {
                ++self->timerCounter;
                if (self->timerCounter>=self->debouncingTime)
                {
                    self->wasPressedOnce = false;
                    self->timerCounter = 0;
                }
                return BS_BOUNCING;
            }

            return BS_UNPRESSED;
    }
}
