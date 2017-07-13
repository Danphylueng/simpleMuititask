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

static __IO u32 _g_time_counter = 0;
__IO u8 _g_time_flag = 0;
 
/**
  * @brief  启动系统滴答定时器 SysTick
  * @param  无
  * @retval 无
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	if (SysTick_Config(SYSTICK_INT_1MS))	// ST3.5.0库版本   /* the system interrlupt in ms */
	{ 
		/* Capture error */ 
		while (1);
	}
	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk; /* open the systick counter */
}

///**
//  * @brief   us延时程序,10us为一个单位
//  * @param  
//  *		@arg nTime: Delay_us( 1 ) 则实现的延时为 1 * 10us = 10us
//  * @retval  无
//  */
//void Delay_us(__IO u32 nTime)
//{ 
//	TimingDelay = nTime;	

//	// 使能滴答定时器  
//	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

//	while(TimingDelay != 0);
//}

///**
//  * @brief  获取节拍程序
//  * @param  无
//  * @retval 无
//  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
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
