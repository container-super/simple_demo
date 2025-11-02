#ifndef _LED_H
#define _LED_H

#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_hal.h"
#include "main.h"

#define LED_Red_PORT                  GPIOB         //B口 
#define LED_Red_PIN                   GPIO_PIN_5    //PB5 红色
#define LED_Red_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)             //PB使能

#define LED_Gre_PORT                  GPIOE        //E口
#define LED_Gre_PIN                   GPIO_PIN_5   //PE5 绿色
#define LED_Gre_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)             //PE使能

#define LED_Red(x)  do{x ?\
                          HAL_GPIO_WritePin(LED_Red_PORT, LED_Red_PIN, GPIO_PIN_SET):\
                          HAL_GPIO_WritePin(LED_Red_PORT, LED_Red_PIN, GPIO_PIN_RESET);\
                      }while(0)   //红色LED翻转运算

#define LED_Gre(x)  do{x ?\
                          HAL_GPIO_WritePin(LED_Gre_PORT, LED_Gre_PIN, GPIO_PIN_SET):\
                          HAL_GPIO_WritePin(LED_Gre_PORT, LED_Gre_PIN, GPIO_PIN_RESET);\
                       }while(0)   //绿色LED翻转运算

#define LED_Red_TOG  do{ HAL_GPIO_TogglePin(LED_Red_PORT, LED_Red_PIN); }while(0)   //红色LED翻转逻辑运算定义
#define LED_Gre_TOG  do{ HAL_GPIO_TogglePin(LED_Gre_PORT, LED_Gre_PIN); }while(0)   //绿色LED翻转逻辑运算定义

void LED_Ctr(void); //LED初始化函数
#endif