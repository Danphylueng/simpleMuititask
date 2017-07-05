#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

#define INTERRUPT_FREQ_1US (0x01 << 0)    					/* 1us generate a interrupt */
#define INTERRUPT_FREQ_10US (0x01 << 1)							/* :10us generate a interrupt */
#define INTERRUPT_FREQ_100US (0x01 << 2)						/* :100us geretate a interrupt */
#define INTERRUPT_FREQ_1MS (0x01 << 3)		  				/* :1ms generate a interrupt */
#define INTERRUPT_FREQ_10MS (0x01 << 4)  						/* :10ms generate a inrerrupt */
#define INTERRUPT_FREQ_100MUS (0x01 << 5)						/* :100ms genetate a interrupt */


typedef struct _task
{
    u8 Run;                 			/*!< the flag to define the task is run or not */
    u16 Timer;              			/*!< the task timer counter */
    u16 ItvTime;            			/*!< the reload timer counter , when the ItvTime == 0 the task is pause ,
																				the frame work will not upgrade the Timer */
    void (*TaskHook)(void); 			/*!< a fuction pointer point to the task fuction */
} task;       										/*!< multi task structure */


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
static void SysTick_Init(u8 interrupt_freq);

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

#endif /* __SYSTICK_H */
