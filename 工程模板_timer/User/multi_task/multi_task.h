#ifndef _MULTI_TASK_H
#define _MULTI_TASK_H

#include "stm32f10x.h"
#include "bsp_TiMbase.h" 


typedef struct _task
{
    u8 Run;                 			/*!< the flag to define the task is run or not */
    u16 Timer;              			/*!< the task timer counter */
    u16 ItvTime;            			/*!< the reload timer counter , when the ItvTime == 0 the task is pause ,
																				the frame work will not upgrade the Timer */
    void (*TaskHook)(void); 			/*!< a fuction pointer point to the task fuction */
} task;       										/*!< multi task structure */


/**
 * \brief    : register the task to the framework 
 * \detail   : register the task to the framework
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
u8 register_the_task(task *task_set, u8 num, u8 interrupt_freq);


/**
 * \brief    : decrease every task timer ,and if the timer == 0 run will be set to 1
 * \detail   : decrease every task timer ,and if the timer == 0 run will be set to 1,it have to be use in the systick interrupt
 *
 * \param[in]: none
 *																				 	
 * \retval : none
 */
void task_timer_updata(void);


/**
 * \brief    : run each task if the time is arrve 
 * \detail   : this fuction will never return
 *
 *																				 	
 * \retval : never return
 */
void task_run_schedule(void);

#endif

