/**
  ******************************************************************************
  * @file    bsp_SysTick.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   SysTick ϵͳ�δ�ʱ��10us�жϺ�����,�ж�ʱ����������ã�
  *          ���õ��� 1us 10us 1ms �жϡ�     
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_SysTick.h"

static __IO u32 _g_time_counter = 0;
__IO u8 _g_time_flag = 0;
 
/**
  * @brief  ����ϵͳ�δ�ʱ�� SysTick
  * @param  ��
  * @retval ��
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0��汾
	if (SysTick_Config(SYSTICK_INT_1MS))	// ST3.5.0��汾   /* the system interrlupt in ms */
	{ 
		/* Capture error */ 
		while (1);
	}
	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk; /* open the systick counter */
}

///**
//  * @brief   us��ʱ����,10usΪһ����λ
//  * @param  
//  *		@arg nTime: Delay_us( 1 ) ��ʵ�ֵ���ʱΪ 1 * 10us = 10us
//  * @retval  ��
//  */
//void Delay_us(__IO u32 nTime)
//{ 
//	TimingDelay = nTime;	

//	// ʹ�ܵδ�ʱ��  
//	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

//	while(TimingDelay != 0);
//}

///**
//  * @brief  ��ȡ���ĳ���
//  * @param  ��
//  * @retval ��
//  * @attention  �� SysTick �жϺ��� SysTick_Handler()����
//  */
//void TimingDelay_Decrement(void)
//{
//	if (TimingDelay != 0x00)
//	{ 
//		TimingDelay--;
//	}
//}




/**
 * \brief    : increase the conter in this fuction. if ms arrve, set the  time_flag to 1
 * \detail   :
 *
 * \param[in]:none
 *
 * \retval : none
 */
void increase_counter(void)
{
	_g_time_counter++;
	
	if (_g_time_counter >= 5) {										/* if 5ms arrve,set _g_time_flag to 1  */
		
		_g_time_flag = 1;	
		_g_time_counter = 0;
	}
}


/*********************************************END OF FILE**********************/
