/********************************************************************************
 * @版本  ：V1.0
 * @文件  : task.c
 * @作者  : caochao
 * @日期  : 9-19-2018
 * @摘要  : 这个C文件时实现了ucosII的启动
 *
 * 修改人 :
 *  日期  :
 *
 * 修改人 :
 *  日期  :
 *******************************************************************************/
#include "stm32f4xx.h"
#include "includes.h"
#include "task.h"
#include  <cpu.h>

/*-----------------------------开始任务堆栈-------------------------------------------*/
OS_TCB     TaskStartTCB;
__align(8) CPU_STK START_TASK_STK[START_STK_SIZE];   //创建任务堆栈空间	

/*----------------------------串口打印堆栈--------------------------------------------*/
OS_TCB     TaskUsart1TCB;
__align(8) CPU_STK USART1_TASK_STK[USART1_STK_SIZE]; //创建任务堆栈空间	

/*-----------------------------LED1任务堆栈------------------------------------------*/
OS_TCB     TaskLed1TCB;
__align(8) CPU_STK LED1_TASK_STK[LED1_STK_SIZE];     //创建任务堆栈空间	

/*-----------------------------LED2任务堆栈------------------------------------------*/
OS_TCB     TaskLed2TCB;
__align(8) CPU_STK LED2_TASK_STK[LED2_STK_SIZE];      //创建任务堆栈空间	

/*-----------------------------LED3任务堆栈------------------------------------------*/
OS_TCB     TaskLed3TCB;
__align(8) CPU_STK LED3_TASK_STK[LED3_STK_SIZE];      //创建任务堆栈空间	

/************************************************************************************
 *   函数名：start_task(void *pdata)
 *   功  能：开始任务，建立其他任务
 *   输  入：
 *          pdata 指针
 *   输  出：
 *          无
 **********************************************************************************/
void start_task(void *pdata)
{
    OS_ERR      err;

	CPU_SR_ALLOC();
    
    CPU_Init();          /* Initialize the uC/CPU services*/
    Systick_Init();      /*Systick初始化函数*/
 
    if(!SYSBSP_Init())
    {
        printf("硬件系统初始化失败！\r\n");
    }

    Mem_Init();          /* Initialize memory managment module                   */
    Math_Init();         /* Initialize mathematical module                       */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);     /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

#if OS_CFG_SCHED_ROUND_ROBIN_EN
    OSSchedRoundRobinCfg(DEF_ENABLED,10,&err);
#endif

    OS_CRITICAL_ENTER();    //进入临界区

    OSTaskCreate((OS_TCB       *)&TaskUsart1TCB,       /* Create the start task                                */
                 (CPU_CHAR     *)"Usart1  Task",
                 (OS_TASK_PTR   )usart1_task,
                 (void         *)0u,
                 (OS_PRIO       )USART1_TASK_PRIO,
                 (CPU_STK      *)&USART1_TASK_STK[0u],
                 (CPU_STK_SIZE  )USART1_STK_SIZE/10u,
                 (CPU_STK_SIZE  )USART1_STK_SIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err); 
                 
    OSTaskCreate((OS_TCB       *)&TaskLed1TCB,       /* Create the start task                                */
                 (CPU_CHAR     *)"led1  Task",
                 (OS_TASK_PTR   )led1_task,
                 (void         *)0u,
                 (OS_PRIO       )LED1_TASK_PRIO,
                 (CPU_STK      *)&LED1_TASK_STK[0u],
                 (CPU_STK_SIZE  )LED1_STK_SIZE/10u,
                 (CPU_STK_SIZE  )LED1_STK_SIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);     

    OSTaskCreate((OS_TCB       *)&TaskLed2TCB,       /* Create the start task                                */
                 (CPU_CHAR     *)"led2  Task",
                 (OS_TASK_PTR   )led2_task,
                 (void         *)0u,
                 (OS_PRIO       )LED2_TASK_PRIO,
                 (CPU_STK      *)&LED2_TASK_STK[0u],
                 (CPU_STK_SIZE  )LED2_STK_SIZE/10u,
                 (CPU_STK_SIZE  )LED2_STK_SIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err); 
 
    OSTaskCreate((OS_TCB       *)&TaskLed3TCB,       /* Create the start task                                */
                 (CPU_CHAR     *)"led3  Task",
                 (OS_TASK_PTR   )led3_task,
                 (void         *)0u,
                 (OS_PRIO       )LED3_TASK_PRIO,
                 (CPU_STK      *)&LED3_TASK_STK[0u],
                 (CPU_STK_SIZE  )LED3_STK_SIZE/10u,
                 (CPU_STK_SIZE  )LED3_STK_SIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err); 

    OSTaskDel(&TaskStartTCB,&err);  //删除开始任务         
    if (err == OS_ERR_NONE)
    {
        printf("开始任务删除成功！\r\n");
    }
    else
    {
        printf("开始任务删除成功! \r\n");
    }
    
    OS_CRITICAL_EXIT(); //退出临界区                 
}

/**********************************************************************************
 *   函数名：usart1_task(void *pdata)
 *   功  能：usart1任务
 *   输  入：
 *          pdata 指针
 *   输  出：
 *          无
 *********************************************************************************/
void usart1_task(void *pdata)
{ 
    while (1)
    {
        printf("CPU的使用率为：%d.%d%%\r\n",OSStatTaskCPUUsage/100,
                                            OSStatTaskCPUUsage%100);
      
		Delay1ms(200);	
    }
}

/**********************************************************************************
 *   函数名：led1_task(void *pdata)
 *   功  能：LED1任务
 *   输  入：
 *          pdata 指针
 *   输  出：
 *          无
 *********************************************************************************/
void led1_task(void *pdata)
{
    LED1_Init();
    
	while (1)
	{	
		LED1_ON;         //LED1灯亮
		Delay1ms(500);
		LED1_OFF;         //LED1灯灭
		Delay1ms(1000);
	}
}

/**********************************************************************************
 *   函数名：led2_task(void *pdata)
 *   功  能：LED2任务
 *   输  入：
 *          pdata 指针
 *   输  出：
 *          无
 *********************************************************************************/
void led2_task(void *pdata)
{ 
    LED2_Init();
    
	while (1)
	{
        LED2_ON;            //LED2灯亮
		Delay1ms(1000);
		LED2_OFF;           //LED2灯灭
		Delay1ms(500);
	}
}

/**********************************************************************************
 *   函数名：led3_task(void *pdata)
 *   功  能：LED3任务
 *   输  入：
 *          pdata 指针
 *   输  出：
 *          无
 *********************************************************************************/
void led3_task(void *pdata)
{
    LED3_Init();
    
	while (1)
	{	
		LED3_ON;          //LED3灯亮
		Delay1ms(250);
		LED3_OFF;         //LED3灯灭
		Delay1ms(250);
	}
}

/************************************文件结束****************************************/
                


