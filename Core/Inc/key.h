#ifndef _KEY_H
#define _KEY_H

#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_hal.h"
#include "main.h"


#define KEY0_PORT                  GPIOE
#define KEY0_PIN                   GPIO_PIN_4
#define KEY0_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define KEY1_PORT                  GPIOE
#define KEY1_PIN                   GPIO_PIN_3
#define KEY1_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define KEY0        HAL_GPIO_ReadPin(KEY0_PORT, KEY0_PIN)     /* 读取KEY0引脚 */
#define KEY1        HAL_GPIO_ReadPin(KEY1_PORT, KEY1_PIN)     /* 读取KEY1引脚 */

#define KEY0_PRES    1              /* KEY0按下 */
#define KEY1_PRES    2              /* KEY1按下 */

void KEY_In(void);                /* 按键初始化函数 */
uint8_t key_scan(uint8_t mode);     /* 按键扫描函数 */

#endif
