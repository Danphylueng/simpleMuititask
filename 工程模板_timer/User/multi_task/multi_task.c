#include "multi_task.h"


static task *g_task_set = 0;														/*<! a pointer point to the task set */
static u8 g_num_of_task = 0;														/*<! how many task  */
 


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
	
	
	TIM6_Configuration(interrupt_freq);
	TIM6_NVIC_Configuration();
	
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
