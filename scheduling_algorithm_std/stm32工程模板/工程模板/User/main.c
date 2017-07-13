/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_Systick.h"
#include "bsp_Timbase.h"
#include "task.h"
#include "bsp_led.h"




extern __IO u8 _g_time_flag;

static uint32_t g_start_tick;
uint32_t g_now_tick;
u16 i;

void fast_loop (void)
{
	/* do something */
	if (i >= 800) {
		i = 0;
		//printf("------fast_loop-----\n");
	} else {
		i++;
	}	
}




/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	
	uint32_t timer          = 0;
	uint32_t timer_         = 0;
	uint16_t time_available = 0;
	
	LED_GPIO_Config();
	SysTick_Init();
	TIM6_Configuration();
	
	g_start_tick = micros();
	g_now_tick   = g_start_tick;
	while (1) {

		
		if (_g_time_flag == 1) {   	/* Wait for the 5ms mark bit */
			
			_g_time_flag = 0;
			
			timer = micros();  	 	/* get current time */
	
			fast_loop();       	 	/* execute the fast_loop task */
			
			tick();             	/* Record number of runs */
			
			timer_ = micros();  	/* get the time after executing fast_loop */
			time_available = (timer + 5000) - timer_;     /* calculate the remaining valid time */
			
			run(time_available);    /* start to schedule */
			
		}
		
		g_now_tick   = micros();	
	
	}
}

/*********************************************END OF FILE**********************/

