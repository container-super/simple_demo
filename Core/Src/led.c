#include "led.h"

void LED_Ctr(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0}; //GPIO初始化结构体

    
    LED_Red_ENABLE(); //使能红色LED端口
    LED_Gre_ENABLE(); //使能绿色LED端口


    HAL_GPIO_WritePin(LED_Red_PORT, LED_Red_PIN, GPIO_PIN_RESET); //初始化红色LED为熄灭状态
    HAL_GPIO_WritePin(LED_Gre_PORT, LED_Gre_PIN, GPIO_PIN_RESET); //初始化绿色LED为熄灭状态


    GPIO_InitStruct.Pin = LED_Red_PIN; //配置红色LED引脚
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; //推挽输出模式
    GPIO_InitStruct.Pull = GPIO_NOPULL; //无上拉下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; //低速
    HAL_GPIO_Init(LED_Red_PORT, &GPIO_InitStruct); //初始化红色LED端口

    GPIO_InitStruct.Pin = LED_Gre_PIN; //配置绿色LED引脚
    HAL_GPIO_Init(LED_Gre_PORT, &GPIO_InitStruct); //初始化绿色LED端口

    LED_Red(1);
    LED_Gre(1);

}