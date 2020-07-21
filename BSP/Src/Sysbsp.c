/********************************************************************************
 * @版本  ：V1.0
 * @文件  : sysbsp.c
 * @作者  : caochao
 * @日期  : 9-19-2018
 * @摘要  : 这个C文件时硬件的初始化
 *
 * 修改人 :
 *  日期  :
 *
 * 修改人 :
 *  日期  :
 
 ********************************************************************************/
#include "stm32f4xx.h"
#include "includes.h"
#include "sysbsp.h"

/*-----------------------------------------------------------------------------*/
FIL       fp;
FATFS     fs;		
FRESULT   res;

/********************************************************************************
 *  函数名:  BSP_Init
 *  功  能:  系统硬件的初始化
 *  输  入:   
 *           无
 *  输  出:   
 *           true：初始化成功
 *          false：初始化失败
 ********************************************************************************/
bool SYSBSP_Init(void)
{ 
    uint8_t  wirteData[20] = "写入数据测试！\r\n";
    uint32_t wirteByteNum;
    
    /*初始化printf串口*/
    USART1_Configuration();

	//挂载文件系统，挂载时会对SDka初始化*/
	res = f_mount(&fs,"1:",1);    
    if(res != FR_OK)
    {
        printf("挂载文件系统失败！\r\n");
    }
    else
    {
        printf("挂载文件系统成功！\r\n");
    }
    
    res = f_open(&fp,"1:test.txt",FA_WRITE|FA_CREATE_ALWAYS);
    if(res != FR_OK)
    {
        printf("创建test.txt文件失败！\r\n");
    }
    else
    {
        printf("创建test.txt文件成功！\r\n");
    }
    
    res = f_write(&fp, wirteData, 20, &wirteByteNum);          
    if(res != FR_OK)
    {
        printf("写入数据失败！\r\n");
    }
    else
    {
        printf("写入数据成功！\r\n");
    }

    /* Close open files */
    f_close(&fp);
    
    return true;
}

/**************************************文件结束*************************************/

