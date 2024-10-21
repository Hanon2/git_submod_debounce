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
            self->pressCount++;
        }
        if(self->longPressDetected)
            return BS_LONG_PRESSED;

        else if (self->timerCounter>=self->debouncingTime)
        {
            self->pressCount++;
            return BS_BOUNCING;
        }


        else
            return BS_BOUNCING;
    }
    else
    {
        if ((self->pressCount>=1) && !self->longPressDetected)
        {
            self->timerCounter = 0;
            self->releaseCounter++;
            if (self->releaseCounter>=self->doublePressGap)
            {
                self->releaseCounter = 0;
                self->pressCount = 0;
                return BS_PRESSED;
            }
            else if (self->pressCount>=2)
            {
                self->releaseCounter = 0;
                self->pressCount = 0;
                return BS_DOUBLE_PRESSED;
            }
            return BS_BOUNCING;
        }
        else
        {
            self->pressCount = 0;
            self->longPressDetected = false;
            self->releaseCounter = 0;
            self->timerCounter = 0;
            return BS_UNPRESSED;
        }

    }
}
