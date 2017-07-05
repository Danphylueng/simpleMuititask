/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_led.h"
#include "multi_task.h"

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
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	task led_task[3] = {{0, 1, 10, led1toggle},
											{0, 2, 20, led2toggle},
											{0, 3, 30, led3toggle}};
	
	LED_GPIO_Config();
	
	register_the_task(led_task, 3, INTERRUPT_FREQ_10US);
	task_run_schedule();										
  	  while(1);
	  /* add your code here ^_^. */
}

/*********************************************END OF FILE**********************/

