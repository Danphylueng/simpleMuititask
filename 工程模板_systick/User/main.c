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
#include "bsp_SysTick.h"
#include "bsp_led.h"

void led1toggle(void)
{
	LED1_TOGGLE;
}

void led2toggle(void)
{
	LED2_TOGGLE;
}

void led3toggle(void)
{
	LED3_TOGGLE;
}
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	task led_task[3] = {{0, 1000, 1000, led1toggle},
											{0, 2000, 2000, led2toggle},
											{0, 3000, 3000, led3toggle}};
	
	LED_GPIO_Config();
	
	register_the_task(led_task, 3, INTERRUPT_FREQ_1MS);
	
	task_run_schedule();
}

/*********************************************END OF FILE**********************/

