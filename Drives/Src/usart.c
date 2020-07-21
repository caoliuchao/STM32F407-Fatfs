/***********************************************************************************
 * @文件  : usart.c
 * @作者  : caochao
 * @日期  : 2-3-2017
 * @摘要  : 这个C文件时定义usart的printf函数的重定向和usart1的初始化
 *
 * 修改人 :
 *  日期  :
 *
 * 修改人 :
 *  日期  :
 **********************************************************************************/
#include <stdio.h>
#include "stm32f4xx.h"
#include "usart.h"

/* 加入以下代码,支持printf函数,而不需要选择use MicroLIB	 */ 
#pragma import(__use_no_semihosting) 

//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
FILE __stdin;

void _ttywrch(int ch) 
{
    while(USART_GetFlagStatus(USART1_PORT, USART_FLAG_TXE) == RESET)
    {
        ;
    }
    
    USART_SendData(USART1_PORT, ch);
}

/* 定义_sys_exit()以避免使用半主机模式  */  
void _sys_exit(int x) 
{ 
	x = x; 
} 

/**********************************************************************************
 *   函数名：fputc(int ch,FILE *p)
 *   功  能：printf函数重定向
 *   输  入：
 *          ch 要打印的字符
 *   输  出：
 *********************************************************************************/
int fputc(int ch,FILE *p)
{
	while (USART_GetFlagStatus(USART1_PORT,USART_FLAG_TC) == RESET)
	{
		;
	}
	
	USART_SendData(USART1_PORT,(uint8_t)ch);
	return ch;
}

/***********************************************************************************
 *   函数名：fgetc(FILE *p)
 *   功  能：scanf函数重定向
 *   输  入：
 *          
 *   输  出：
 *          接收到的字符
 **********************************************************************************/
int fgetc(FILE *p)
{
	while (USART_GetFlagStatus(USART1_PORT,USART_FLAG_RXNE) == RESET)
	{
		;
	}
    
	return USART_ReceiveData(USART1_PORT);
}

/*************************************************************************************
 *  函数名:   USART1_Configuration
 * 函数功能:  usart的功能设置
 * 输    入:   
 *           无 
 * 输    出:   
 *           无
 ***********************************************************************************/
void USART1_Configuration(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_AHB1PeriphClockCmd(USART1_TX_PERIPH,ENABLE);       //打开GPIOA的时钟  
    RCC_AHB1PeriphClockCmd(USART1_RX_PERIPH,ENABLE);       //打开GPIOA的时钟  
    RCC_APB2PeriphClockCmd(USART1_PERIPH ,ENABLE);         //打开usart1时钟
    
	GPIO_PinAFConfig(USART1_TX_PORT,USART1_TX_AF_PIN,USART1_TX_AF);  //GPIO复用为USART1
	GPIO_PinAFConfig(USART1_RX_PORT,USART1_RX_AF_PIN,USART1_RX_AF); //GPIO复用为USART1
    
    GPIO_InitStructure.GPIO_Pin	= USART1_TX_PIN  ; //GPIO为复用推挽输出模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    
    GPIO_Init(USART1_TX_PORT,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin	= USART1_RX_PIN ; //GPIO为复用推挽输出模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    
	GPIO_Init(USART1_RX_PORT,&GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = USART1_BaudRate;         //波特率设置为9600
	USART_InitStructure.USART_WordLength  = USART_WordLength_8b;  //发送数据为8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;        //停止位为1
	USART_InitStructure.USART_Parity = USART_Parity_No;           //不进行奇偶位检测
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件流
    USART_InitStructure.USART_Mode =  USART_Mode_Rx | USART_Mode_Tx;     //允许usart接受和发送数据
    USART_Init(USART1_PORT,&USART_InitStructure);         //初始化usart

	USART_Cmd(USART1_PORT,ENABLE);                  //启动usart                                                         
}

/************************************文件结束*****************************************/

