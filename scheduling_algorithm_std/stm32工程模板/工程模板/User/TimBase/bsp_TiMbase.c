/**
  ******************************************************************************
  * @file    bsp_TimBase.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   TIM6 1ms 定时应用bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "bsp_TiMbase.h" 

__IO u32 g_time_val = 0;													/*!< use to recotd the time (ms), if the system work 50 days this variable will over flow*/

/// TIM6中断优先级配置
void TIM6_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * \brief    :this fuction use to increase the _g_time_val, this fuction is called in TIM IRQ handle fuction
 * \detail   :
 *
 *
 * \retval : none
 */
void time_count(void)
{
	 g_time_val++;
}

/*
 * TIM_Period / Auto Reload Register(ARR) = 1000   TIM_Prescaler--71 
 * 中断周期为 = 1/(72MHZ /72) * 1000 = 1ms
 *
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIM_Period(ARR) --> 中断 且TIMxCNT重置为0重新计数 
 */
void TIM6_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		/* 设置TIM6CLK 为 72MHZ */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);
    //TIM_DeInit(TIM6);
	
	/* 自动重装载寄存器周期的值(计数值) */
    TIM_TimeBaseStructure.TIM_Period=1000;
	
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
	  /* 时钟预分频数为72 */
    TIM_TimeBaseStructure.TIM_Prescaler= 72;
	
		/* 对外部时钟进行采样的时钟分频,这里没有用到 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	
    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
		
    TIM_Cmd(TIM6, ENABLE);																		
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , DISABLE);		/*先关闭等待使用*/    
}






/**
 * \brief get the program run time (millisecond)
 *
 * \retval : return the sys time in ms
 */
uint32_t millis (void)
{
	return g_time_val;
}

/**
 * \brief get the timer counter value (millisecond)
 *
 * \retval : return the timer counter
 */
uint32_t get_timer_counter (void)
{
	return TIM6->CNT;
}

/**
 * \brief get the program run time (microsecond)
 *
 * \retval : return the sys time in us
 */
uint32_t micros (void)
{
	return g_time_val * 1000 + get_timer_counter();
}

/*********************************************END OF FILE**********************/
