/*************************************************************************************
 * @文件  : led.c
 * @作者  : caochao
 * @日期  : 22-9-2017
 * @摘要  : 这个C文件时实现led的初始化
 *
 * 修改人 :
 *  日期  :
 *
 * 修改人 :
 *  日期  :
 *************************************************************************************/
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "led.h"

/*************************************************************************************
 *   函数名：LED1_Init(void)
 *   功  能：LED1管脚的初始化
 *   输  入：
 *           无
 *   输  出：
 *           无
 ************************************************************************************/
void LED1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	 
    RCC_AHB1PeriphClockCmd(LED1_PERIPH,ENABLE);         //打开GPIOE的时钟      
    
    GPIO_InitStructure.GPIO_Pin = LED1_PIN;            //GPIOE.3为推挽输出模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	
	GPIO_Init(LED1_PORT,&GPIO_InitStructure);
}	

/************************************************************************************
 *   函数名：LED2_Init(void)
 *   功  能：LED2管脚的初始化
 *   输  入：
 *           无
 *   输  出：
 *           无
 ***********************************************************************************/
void LED2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	 
    RCC_AHB1PeriphClockCmd(LED2_PERIPH,ENABLE);         //打开GPIOE的时钟      
    
    GPIO_InitStructure.GPIO_Pin = LED2_PIN;            //GPIOE.4为推挽输出模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	
	GPIO_Init(LED2_PORT,&GPIO_InitStructure);
}	

/************************************************************************************
 *   函数名：LED3_Init(void)
 *   功  能：LED2管脚的初始化
 *   输  入：
 *           无
 *   输  出：
 *           无
 ***********************************************************************************/
void LED3_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	 
    RCC_AHB1PeriphClockCmd(LED3_PERIPH,ENABLE);         //打开GPIOE的时钟      
    
    GPIO_InitStructure.GPIO_Pin = LED3_PIN;            //GPIOE.4为推挽输出模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	
	GPIO_Init(LED3_PORT,&GPIO_InitStructure);
}

/********************************文件结束********************************************/


