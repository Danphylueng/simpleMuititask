#include "task.h"
#include "bsp_TiMbase.h" 
#include "bsp_SysTick.h"
#include "bsp_led.h"  


/************************************************
You need to declare the function before the call
*************************************************/
void led1_task_func (void);
void led2_task_func (void);
void led3_task_func (void);
void uart_task_func (void);
void uart_task_func_2(void);


/************************************************
 this is your tasks array
*************************************************/
static task_components task_array[] = 
{
    {uart_task_func,       1,    40},
    {led1_task_func,        4,    10},
    {led2_task_func,        2,    10},
		{led3_task_func,        1,    10}
}; 


/************************************************
 you can add tasks here
*************************************************/
void led1_task_func (void)
{
	LED1_TOGGLE;
}
void led2_task_func (void)
{
	LED2_TOGGLE;
}

void led3_task_func (void)
{
	LED3_TOGGLE;
}


void uart_task_func (void)
{

}


uint32_t g_tick_counter = 0;

uint16_t  g_last_run[ARRAY_LEN(task_array)] = {0};
uint32_t _task_time_allowed = 0;
uint32_t _task_time_started = 0;
uint8_t   current_task 		= 0;
uint32_t  time_taken 		= 0;

/**
 * \brief  The main scheduling function 
 * 
 * \param[in]  time_available:The remaining time after running the fast_loop
 *
 * \note this is the main scheduling function which is referring to ardupolit.
 *       it can run regularly with some question such that not do some error 
 *       handling
 *
 */
void run (uint16_t time_available)
{
	uint32_t now = micros();
	uint8_t i = 0;
	
	for (i = 0; i < ARRAY_LEN(task_array); i++) {
		uint16_t dt = g_tick_counter - g_last_run[i];
        uint16_t interval_ticks = 200 / task_array[i].rate_hz;
		
        if (interval_ticks < 1) {
            interval_ticks = 1;
        }
		
		if (dt >= interval_ticks) {
            // this task is due to run. Do we have enough time to run it?
            _task_time_allowed = task_array[i].max_time_micros;

            if (dt >= interval_ticks * 2) {																														/* sliped sevetal this task , this mean the task should run some time but we don't run it */
				//todo
                // we've slipped a whole run of this task!
                //printf some information about task;
				
            }
			if (_task_time_allowed <= time_available) {
                // run it
                _task_time_started = now;
                current_task = i;
                task_array[i].taskhook();

                // record the tick counter when we ran. This drives
                // when we next run the event
                g_last_run[i] = g_tick_counter;

                // work out how long the event actually took
                now        = micros();
                time_taken = now - _task_time_started;

                if (time_taken > _task_time_allowed) {
					//todo
                    // the event overran!
                    //printf error
                }
				
                if (time_taken >= time_available) {
					//todo
                }
                time_available -= time_taken;
				}
     }
  }
		
}

/**
 * \brief  fast_loop running ticks
 *
 */
void tick (void)
{
	g_tick_counter++;
}


