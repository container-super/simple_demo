#include "key.h"
#include "delay.h"
#include "stm32f1xx_hal_gpio.h"

void KEY_In(void)
{
    GPIO_InitTypeDef  huart1_Handle;
    KEY0_ENABLE();                                    
    KEY1_ENABLE();                                     

     huart1_Handle.Pin = KEY0_PIN;                    // 配置KEY0引脚      
     huart1_Handle.Mode = GPIO_MODE_INPUT;            // 输入模式
     huart1_Handle.Pull = GPIO_PULLUP;                // 上拉输入
     huart1_Handle.Speed = GPIO_SPEED_FREQ_HIGH;      // 高速
    HAL_GPIO_Init(KEY0_PORT, & huart1_Handle);        // 初始化KEY0端口

     huart1_Handle.Pin = KEY1_PIN;
     huart1_Handle.Mode = GPIO_MODE_INPUT;
     huart1_Handle.Pull = GPIO_PULLUP;
     huart1_Handle.Speed = GPIO_SPEED_FREQ_HIGH; 
    HAL_GPIO_Init(KEY1_PORT, & huart1_Handle);

}

uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* 支持连按 */

    if (key_up && (KEY0 == 0 || KEY1 == 0 ))  /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        delay_ms(10);           /* 去抖动 */
        key_up = 0;

        if (KEY0 == 0)  keyval = KEY0_PRES;

        if (KEY1 == 0)  keyval = KEY1_PRES;

    }
    else if (KEY0 == 1 && KEY1 == 1 ) /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }

    return keyval;              /* 返回键值 */
}