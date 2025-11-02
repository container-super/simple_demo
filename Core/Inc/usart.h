#ifndef __USART_H 
#define __USART_H

#include "stdio.h"
#include "sys.h"

extern UART_HandleTypeDef  huart1_Handle;

#define USART_TX_PORT   GPIOA
#define USART_TX_PIN    GPIO_PIN_9
#define USART_TX_EN()     do{__HAL_RCC_GPIOA_CLK_ENABLE();}while(0);

#define USART_RX_PORT   GPIOA
#define USART_RX_PIN    GPIO_PIN_10
#define USART_RX_EN()     do{__HAL_RCC_GPIOA_CLK_ENABLE(); }while(0);

#define USART_UX                USART1                                        //串口1
#define USART_UX_IRQn           USART1_IRQn                                   //串口1中断
#define USART_UX_IRQHandler     USART1_IRQHandler                             //串口1中断服务函数 
#define USART_UX_EN()           do{ __HAL_RCC_USART1_CLK_ENABLE(); }while(0)  //USART1 时钟使能


#define USART_Data_Len  256  //接收数据长度
#define USART_EN_RX     1    //使能接收
#define RX_BUFFER_SIZE    1    //接收缓冲区大小

extern uint8_t  usart_rx_buf[USART_Data_Len];  //接收缓冲变量
extern uint16_t usart_rx_sta;                 //接收状态标记
extern uint8_t rx_buffer[RX_BUFFER_SIZE];       //HAL库USART接收Buffer

void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart);

void usart_init(uint32_t bound);    
  
uint8_t is_receive_complete(void);
uint16_t get_receive_length(void);
void clear_receive_status(void);

void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart);
void usart_init(uint32_t bound);    
#endif  