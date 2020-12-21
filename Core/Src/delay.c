#include "delay.h"

void delay_us(uint32_t nus)
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * nus);
    while (delay--)
    {
        ;
    }
}
