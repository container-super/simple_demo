#include "sys.h"
#include "usart.h"
#include "stdio.h"
#include <stdint.h>
#include <string.h>
#include "led.h"

UART_HandleTypeDef  huart1_Handle;

// printf支持
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart1_Handle, (uint8_t *)&ch, 1, 1000);
    return ch;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        __io_putchar(*ptr++);
    }
    return len;
}

uint8_t usart_rx_buf[USART_Data_Len];
uint16_t usart_rx_sta = 0;
uint8_t rx_buffer[RX_BUFFER_SIZE];
uint8_t rx_index = 0;  // 添加接收索引

void usart_init(uint32_t bound)
{
    huart1_Handle.Instance = USART_UX;
    huart1_Handle.Init.BaudRate = bound;
    huart1_Handle.Init.WordLength = UART_WORDLENGTH_8B;
    huart1_Handle.Init.StopBits = UART_STOPBITS_1;
    huart1_Handle.Init.Parity = UART_PARITY_NONE;
    huart1_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1_Handle.Init.Mode = UART_MODE_RX | UART_MODE_TX;
    huart1_Handle.Init.OverSampling = UART_OVERSAMPLING_16;
    
    if (HAL_UART_Init(&huart1_Handle) != HAL_OK)
    {
        while(1);  // 初始化失败
    }
    
    // 启动接收中断
    HAL_UART_Receive_IT(&huart1_Handle, rx_buffer, 1);
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (huart->Instance == USART_UX)
    {
        //使能时钟
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();
      
        //配置TX引脚
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
      
        //配置RX引脚
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        //设置中断优先级
        HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART_UX)
    {
        //检查是否为结束符
        if(rx_buffer[0] == '\r' || rx_buffer[0] == '\n') 
        {
            //如果是结束符且已经有数据，则标记接收完成
            if(rx_index > 0) 
            {
                usart_rx_sta = 0x8000 | rx_index;  // 最高位标记完成，低14位为长度
            }
        }
        else 
        {
            //存储数据
            if(rx_index < USART_Data_Len - 1) 
            {
                usart_rx_buf[rx_index++] = rx_buffer[0];
            }
        }
        
        //重新启动接收中断
        HAL_UART_Receive_IT(huart, rx_buffer, 1);
    }
}

//中断处理函数
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart1_Handle);
}

//接收完成检查函数
uint8_t is_receive_complete(void)
{
    return (usart_rx_sta & 0x8000) ? 1 : 0;
}

//获取接收数据函数
uint16_t get_receive_length(void)
{
    return usart_rx_sta & 0x3FFF;
}

//清除接收状态函数
void clear_receive_status(void)
{
    usart_rx_sta = 0;
    rx_index = 0;
    memset(usart_rx_buf, 0, USART_Data_Len);
}