/********************************************************************************
 * @�汾  ��V1.0
 * @�ļ�  : task.c
 * @����  : caochao
 * @����  : 9-19-2018
 * @ժҪ  : ���C�ļ�ʱʵ����ucosII������
 *
 * �޸��� :
 *  ����  :
 *
 * �޸��� :
 *  ����  :
 *******************************************************************************/
#include "stm32f4xx.h"
#include "includes.h"
#include "task.h"
#include  <cpu.h>

/*-----------------------------��ʼ�����ջ-------------------------------------------*/
OS_TCB     TaskStartTCB;
__align(8) CPU_STK START_TASK_STK[START_STK_SIZE];   //���������ջ�ռ�	

/*----------------------------���ڴ�ӡ��ջ--------------------------------------------*/
OS_TCB     TaskUsart1TCB;
__align(8) CPU_STK USART1_TASK_STK[USART1_STK_SIZE]; //���������ջ�ռ�	

/*-----------------------------LED1�����ջ------------------------------------------*/
OS_TCB     TaskLed1TCB;
__align(8) CPU_STK LED1_TASK_STK[LED1_STK_SIZE];     //���������ջ�ռ�	

/*-----------------------------LED2�����ջ------------------------------------------*/
OS_TCB     TaskLed2TCB;
__align(8) CPU_STK LED2_TASK_STK[LED2_STK_SIZE];      //���������ջ�ռ�	

/*-----------------------------LED3�����ջ------------------------------------------*/
OS_TCB     TaskLed3TCB;
__align(8) CPU_STK LED3_TASK_STK[LED3_STK_SIZE];      //���������ջ�ռ�	

/************************************************************************************
 *   ��������start_task(void *pdata)
 *   ��  �ܣ���ʼ���񣬽�����������
 *   ��  �룺
 *          pdata ָ��
 *   ��  ����
 *          ��
 **********************************************************************************/
void start_task(void *pdata)
{
    OS_ERR      err;

	CPU_SR_ALLOC();
    
    CPU_Init();          /* Initialize the uC/CPU services*/
    Systick_Init();      /*Systick��ʼ������*/
 
    if(!SYSBSP_Init())
    {
        printf("Ӳ��ϵͳ��ʼ��ʧ�ܣ�\r\n");
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

    OS_CRITICAL_ENTER();    //�����ٽ���

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

    OSTaskDel(&TaskStartTCB,&err);  //ɾ����ʼ����         
    if (err == OS_ERR_NONE)
    {
        printf("��ʼ����ɾ���ɹ���\r\n");
    }
    else
    {
        printf("��ʼ����ɾ���ɹ�! \r\n");
    }
    
    OS_CRITICAL_EXIT(); //�˳��ٽ���                 
}

/**********************************************************************************
 *   ��������usart1_task(void *pdata)
 *   ��  �ܣ�usart1����
 *   ��  �룺
 *          pdata ָ��
 *   ��  ����
 *          ��
 *********************************************************************************/
void usart1_task(void *pdata)
{ 
    while (1)
    {
        printf("CPU��ʹ����Ϊ��%d.%d%%\r\n",OSStatTaskCPUUsage/100,
                                            OSStatTaskCPUUsage%100);
      
		Delay1ms(200);	
    }
}

/**********************************************************************************
 *   ��������led1_task(void *pdata)
 *   ��  �ܣ�LED1����
 *   ��  �룺
 *          pdata ָ��
 *   ��  ����
 *          ��
 *********************************************************************************/
void led1_task(void *pdata)
{
    LED1_Init();
    
	while (1)
	{	
		LED1_ON;         //LED1����
		Delay1ms(500);
		LED1_OFF;         //LED1����
		Delay1ms(1000);
	}
}

/**********************************************************************************
 *   ��������led2_task(void *pdata)
 *   ��  �ܣ�LED2����
 *   ��  �룺
 *          pdata ָ��
 *   ��  ����
 *          ��
 *********************************************************************************/
void led2_task(void *pdata)
{ 
    LED2_Init();
    
	while (1)
	{
        LED2_ON;            //LED2����
		Delay1ms(1000);
		LED2_OFF;           //LED2����
		Delay1ms(500);
	}
}

/**********************************************************************************
 *   ��������led3_task(void *pdata)
 *   ��  �ܣ�LED3����
 *   ��  �룺
 *          pdata ָ��
 *   ��  ����
 *          ��
 *********************************************************************************/
void led3_task(void *pdata)
{
    LED3_Init();
    
	while (1)
	{	
		LED3_ON;          //LED3����
		Delay1ms(250);
		LED3_OFF;         //LED3����
		Delay1ms(250);
	}
}

/************************************�ļ�����****************************************/
                


