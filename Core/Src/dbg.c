#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "dbg.h"
#include "usart.h"

#ifdef DBG_USE_TIM
#include "tim.h"

/// USB·���ڽ��ջ���
#define DBG_RX_LEN 128
uint8_t DBG_RX_DAT = 0;
uint8_t DBG_RX_BUF[DBG_RX_LEN];
__IO uint16_t DBG_RX_STA = 0;


/// ���庯������ָ��
typedef int (*cmd_process)(const uint8_t* buf, uint32_t len);


/// AT�������
static int cmd_test(const uint8_t* buf, uint32_t len);


/// AT����������
cmd_process at_cmd_process_table[] =
{
    cmd_test,
};

/// ����USB���ݽ��ճ�ʱ��ʱ��
static void dbg_tim_set(int mode)
{
    if (mode)
    {
        __HAL_TIM_SET_COUNTER(dbg_tim_handle, 0);
        HAL_TIM_Base_Start_IT(dbg_tim_handle);
    }
    else
    {
        HAL_TIM_Base_Stop_IT(dbg_tim_handle);
    }
}


/// ��ʱ����ʱ�ص�����
void dbg_tim_callback(void)
{
    dbg_tim_set(0);              // ֹͣ��ʱ��
    DBG_RX_BUF[DBG_RX_STA] = 0;  // ��ӽ�����
    DBG_RX_STA |= 0X8000;        // ������ݽ��ս���
}

/// usb·���ڽ��ջص�����
void dbg_uart_recv_callback(void)
{
    __HAL_TIM_SET_COUNTER(dbg_tim_handle, 0);  // �����ʱ��ʱ������
    if (DBG_RX_STA == 0)                         // ����ǵ�һ�ν�����������ʱ��
    {
        dbg_tim_set(1);
    }
    if (DBG_RX_STA < DBG_RX_LEN)
    {
        DBG_RX_BUF[DBG_RX_STA++] = DBG_RX_DAT;   // ��������
    }
    HAL_UART_Receive_IT(dbg_uart_handle, &DBG_RX_DAT, 1);  // �ٴ�ע�����
}

int cmd_test(const uint8_t* buf, uint32_t len)
{
    return 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == dbg_uart_handle->Instance)
    {
        dbg_uart_recv_callback();
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == dbg_tim_handle->Instance)
    {
        dbg_tim_callback();
    }
}

/// USB���ݴ���
inline void dbg_recv_handler(void)
{
    if (DBG_RX_STA & 0X8000)
    {
        switch(DBG_RX_BUF[0])
        {
        case 0X00:
            break;
        case 0X01:
            break;
        case 0X02:
            break;
        case 0X03:
            break;
        default:
            break;
        }
        DBG_RX_STA = 0;
    }
}

#endif  // DBG_US_TIM


/// ��ʼ��USB
void dbg_init(void)
{
#ifdef DBG_USE_TIM
    HAL_UART_Receive_IT(dbg_uart_handle, &DBG_RX_DAT, 1);  // ע��USB·�����ж�
#endif
}

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
    while (__HAL_UART_GET_FLAG(dbg_uart_handle, UART_FLAG_TXE) != SET);
    dbg_uart_handle->Instance->DR = (uint8_t)(ch & 0XFF);
    return ch;
}

void UARTx_SendData(UART_HandleTypeDef *huart, const void* buf, uint32_t len)
{
    const uint8_t* p = (const uint8_t *)buf;
    while (len--)
    {
        while (__HAL_UART_GET_FLAG(huart, UART_FLAG_TXE) != SET);
        huart->Instance->DR = *p++;
    }
}

void dbg_printf(const void *fmt, ...)
{
    char buf[128];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf, (char*) fmt, ap);
    va_end(ap);
    UARTx_SendData(dbg_uart_handle, buf, strlen(buf));
}
