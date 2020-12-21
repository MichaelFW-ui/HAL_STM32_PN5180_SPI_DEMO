#ifndef DELAY_H__
#define DELAY_H__

#include "main.h"

#define delay_ms(nms) HAL_Delay(nms)
void delay_us(uint32_t nus);

#endif
