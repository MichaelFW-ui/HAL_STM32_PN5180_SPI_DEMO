#ifndef dbg_H__
#define dbg_H__

#include "main.h"

#define STM32_Reset()  do{__disable_irq();NVIC_SystemReset();}while(0)

#define DEBUG_PRINTF

#ifdef DEBUG_PRINTF
#define debug_e(fmt, ...) dbg_printf("[error]:%s:%s():%d,---==>:" fmt "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define debug_w(fmt, ...) dbg_printf("[warning]:%s:%s():%d,---==>:" fmt "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define debug(fmt, ...) dbg_printf(fmt, ##__VA_ARGS__)
#else
#define debug_e(fmt, ...)
#define debug_w(fmt, ...)
#define debug(fmt, ...)
#endif


#define dbg_uart_handle   (&huart1)
#define dbg_tim_handle  (&htim1)

#define DBG_SendData(buf,len) UARTx_SendData(dbg_uart_handle, buf,len)

void dbg_printf(const void *fmt, ...);
void dbg_init(void);
void dbg_recv_handler(void);
void dbg_uart_recv_callback(void);
void dbg_tim_callback(void);
void dbg_dbg_printf(const void *fmt, ...);

#endif
