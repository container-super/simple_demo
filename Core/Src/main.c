#include "led.h"
#include "stm32f1xx_hal.h" 
#include "stm32f1xx_ll_system.h" 
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include <stdio.h>

int main(void) 
{
    HAL_Init(); 
    sys_stm32_clock_init(RCC_PLL_MUL9); 
    delay_init(72); 
    LED_Ctr(); 
    
    // 初始化串口
    usart_init(115200);
    
    printf("System Started. Send commands: R1, R0, G1, G0 (end with Enter)\r\n");

    while (1) 
    {
        // 使用新的检查函数
        if(is_receive_complete()) 
        {   
            uint16_t len = get_receive_length();
            
            printf("Received command: ");
            for(int i = 0; i < len; i++) {
                printf("%c", usart_rx_buf[i]);
            }
            printf("\r\n");
            
            // 处理命令
            if(len >= 2)
            {
                if(usart_rx_buf[0] == 'R')
                {
                    if(usart_rx_buf[1] == '1') {
                        LED_Red(0);  // 开启红色LED
                        printf("Red LED ON\r\n");
                    }
                    else if(usart_rx_buf[1] == '0') {
                        LED_Red(1);  // 关闭红色LED
                        printf("Red LED OFF\r\n");
                    }
                    else {
                        printf("Invalid R command: %c\r\n", usart_rx_buf[1]);
                    }
                }
                else if(usart_rx_buf[0] == 'G')
                {
                    if(usart_rx_buf[1] == '1') {
                        LED_Gre(0);  // 开启绿色LED
                        printf("Green LED ON\r\n");
                    }
                    else if(usart_rx_buf[1] == '0') {
                        LED_Gre(1);  // 关闭绿色LED
                        printf("Green LED OFF\r\n");
                    }
                    else {
                        printf("Invalid G command: %c\r\n", usart_rx_buf[1]);
                    }
                }
                else {
                    printf("Unknown command: %c%c\r\n", usart_rx_buf[0], usart_rx_buf[1]);
                }
            }
            else {
                printf("Command too short: length=%d\r\n", len);
            }
            
            // 清除接收状态，准备下一次接收
            clear_receive_status();
        }
        
        HAL_Delay(10);
    }
}