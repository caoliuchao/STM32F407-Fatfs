/************************************************************************
* @文件  : sys.h
* @作者  : caochao
* @日期  : 10-1-2018
* @摘要  : 这个头文件包含了systick相关函数声明
* 修改人 :
*  日期  :
*
* 修改人 :
*  日期  :
************************************************************************/
/* 定义防止递归的包容 */
#ifndef _SYS_H
#define _SYS_H

#ifdef __cplusplus
 extern "C" {
#endif

#define SYSTEM_SUPPORT_OS		1   //定义系统文件夹是否支持UCOS
     
/*---------------------------需要的头文件-------------------------------*/     
#include "stm32f4xx.h"
 
/*---------------------------全局变量宏定义-----------------------------*/     
#ifdef  DELAY_GLOBALS   
#define DELAY_GLOBALS      
#else   
#define DELAY_GLOBALS  extern
#endif
 
/*---------------------------------------------------------------------*/
DELAY_GLOBALS uint8_t  fac_us;      //us延时倍乘数
DELAY_GLOBALS uint16_t fac_ms;      //ms延时倍乘数

/*
因为没有定义DELAY_GLOBALS这个宏 上式等价于下面两句

extern uint8_t  fac_us;      //us延时倍乘数
extern uint16_t fac_ms;      //ms延时倍乘数
*/

/*----------------------------函数的声明--------------------------------*/     
void Systick_Init(void);   
     
#ifdef __cplusplus
}
#endif

#endif /*sys.h*/
/***************************文件结束**************************************/


