/**
  ******************************************************************************
  * @file    bsp_SysTick.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   SysTick 系统滴答时钟10us中断函数库,中断时间可自由配置，
  *          常用的有 1us 10us 1ms 中断。     
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_SysTick.h"






static task *g_task_set = 0;														/*<! a pointer point to the task set */
static u8 g_num_of_task = 0;														/*<! how many task  */
 
/**
 * \brief    : this fuction is use to init the systick
 * \detail   : init systick according to the interrupt_freq.
 *
 * \param[in]: this parameter should be :    INTERRUPT_FREQ_1US    :1us generate a interrupt
 *																				 	 INTERRUPT_FREQ_10US		:10us generate a interrupt
 *																					 INTERRUPT_FREQ_100US		:100us geretate a interrupt
 *																					 INTERRUPT_FREQ_1MS		  :1ms generate a interrupt
 *																					 INTERRUPT_FREQ_10MS  	:10ms generate a inrerrupt
 *																					 INTERRUPT_FREQ_100MUS	:100ms genetate a interrupt
 *
 * \retval : 
 * \retval :
 */
static void SysTick_Init(u8 interrupt_freq)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	switch (interrupt_freq) {
		
		
	case INTERRUPT_FREQ_1US:
		if (SysTick_Config(SystemCoreClock / 1000000))	// ST3.5.0库版本 /* set 1ms creat a interrupt */
		{ 
			/* Capture error */ 
			while (1);
		}
		break;
		
	case INTERRUPT_FREQ_10US: 
		
		if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0库版本 /* set 1ms creat a interrupt */
		{ 
			/* Capture error */ 
			while (1);
		}
		break;
		
	case INTERRUPT_FREQ_100US:
		if (SysTick_Config(SystemCoreClock / 10000))	// ST3.5.0库版本 /* set 1ms creat a interrupt */
		{ 
			/* Capture error */ 
			while (1);
		}
		break;
		
	case INTERRUPT_FREQ_1MS: 
		if (SysTick_Config(SystemCoreClock / 1000))	// ST3.5.0库版本 /* set 1ms creat a interrupt */
		{ 
			/* Capture error */ 
			while (1);
		}	
		break;
	case INTERRUPT_FREQ_10MS: 
		if (SysTick_Config(SystemCoreClock / 100))	// ST3.5.0库版本 /* set 1ms creat a interrupt */
		{ 
			/* Capture error */ 
			while (1);
		}	
		break;
	case INTERRUPT_FREQ_100MUS: 
		if (SysTick_Config(SystemCoreClock / 10))	// ST3.5.0库版本 /* set 1ms creat a interrupt */
		{ 
			/* Capture error */ 
			while (1);
		}	
	break;
	default:
		while(1);
			
		
	}
	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk; /* open the systick */
}




/**
 * \brief    : register the task to the frame 
 * \detail   : register the task to the frame
 *
 * \param[in]: *task_set : a pointer point the task 
 * \param[in]: num : the num of the task 
 *
 * \param[in]: this parameter should be :   INTERRUPT_FREQ_1US    :1us generate a interrupt
 *																				 	 INTERRUPT_FREQ_10US		:10us generate a interrupt
 *																					 INTERRUPT_FREQ_100US		:100us geretate a interrupt
 *																					 INTERRUPT_FREQ_1MS		  :1ms generate a interrupt
 *																					 INTERRUPT_FREQ_10MS  	:10ms generate a inrerrupt
 *																					 INTERRUPT_FREQ_100MUS	:100ms genetate a interrupt
 * \retval : 1 :success
 * \retval : 0 :failure , the task have already register in the frame work
 */
u8 register_the_task(task *task_set, u8 num, u8 interrupt_freq)
{
	
	if (g_task_set || g_num_of_task) { /* the task have already register in the frame work  */
		
	 return 0;
	}
	
	g_task_set = task_set;
	g_num_of_task = num;
	
	SysTick_Init(interrupt_freq);
	
	return 1;
}


/**
 * \brief    : decrease every task timer ,and if the timer == 0 run will be set to 1
 * \detail   : decrease every task timer ,and if the timer == 0 run will be set to 1,it have to be use in the systick interrupt
 *
 * \param[in]: none
 *																				 	
 * \retval : none
 */
void task_timer_updata(void) 
{
	u8 i;
	for (i = 0; i < g_num_of_task; i++) {  			/* loop through every task */
		
	 if ((g_task_set + i)->ItvTime) {						/* the task is pause or not */
			
			if ((g_task_set + i)->Timer) {					/* if the timer greater than zero, decrease 1 */
				
				 (g_task_set + i)->Timer--; 
			} else {																/* if the timer == 0 set the run to 1 and set the timer to reload time */
					 
					(g_task_set + i)->Timer = (g_task_set + i)->ItvTime;  
					(g_task_set + i)->Run = 1;           
				 
			}
	 }
  }
}

/**
 * \brief    : run each task if the time is arrve 
 * \detail   : this fuction will never return
 *
 *																				 	
 * \retval : never return
 */
void task_run_schedule(void)
{	
	u8 i = 0; 
	while (1) {
  
	 for (i  = 0; i < g_num_of_task; i++) {				/* loop back every task */
		 
		if ((g_task_set + i)->ItvTime) { 						/* the task is pause or not  */
			
			 if ((g_task_set + i)->Run) {							/* if the flag run == 1 the task will be excute */
				 
				 (g_task_set + i)->TaskHook();     	 		/* run the task */
				 (g_task_set + i)->Run = 0;         		/* reset the task to zero */
			 }
		}
	 }  
	}

}
/*********************************************END OF FILE**********************/
