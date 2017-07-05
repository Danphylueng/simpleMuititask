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
 * \brief    :config the timer6 to generate a interrupt.
 * \detail   :
 *
 * \param[in]: interrupt_freq: this parameter should be :   INTERRUPT_FREQ_1US    :1us generate a interrupt
 *																				 	 INTERRUPT_FREQ_10US		:10us generate a interrupt
 *																					 INTERRUPT_FREQ_100US		:100us geretate a interrupt
 *																					 INTERRUPT_FREQ_1MS		  :1ms generate a interrupt
 *																					 INTERRUPT_FREQ_10MS  	:10ms generate a inrerrupt
 *																					 INTERRUPT_FREQ_100MUS	:100ms genetate a interrupt
 *
 * \retval : 0: failure to config the timer pwm output,there is the confilct between clock_div andperiod 
 *					 1: success to config the timer pwm output
 */
u8 TIM6_Configuration(u32 interrupt_freq)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	switch (interrupt_freq) {
		
		
	case INTERRUPT_FREQ_1US:
		
	
		TIM_TimeBaseStructure.TIM_Prescaler= 0; 
		TIM_TimeBaseStructure.TIM_Period = 71; 											/* 72 -1 =1 */
		break;
		
	case INTERRUPT_FREQ_10US: 
		
		TIM_TimeBaseStructure.TIM_Prescaler= 71;									/* 72 - 1 */
		TIM_TimeBaseStructure.TIM_Period = 9;											/* 9 - 1 */
		break;
		
	case INTERRUPT_FREQ_100US:
		
		TIM_TimeBaseStructure.TIM_Prescaler= 71;									/* 72 - 1 */
		TIM_TimeBaseStructure.TIM_Period = 99;										/* 100 - 1 */
		break;
		
	case INTERRUPT_FREQ_1MS: 
		
		TIM_TimeBaseStructure.TIM_Prescaler= 71;									/* 72 - 1 */
		TIM_TimeBaseStructure.TIM_Period = 999;										/* 1000 - 1 */
		break;
		
	case INTERRUPT_FREQ_10MS: 
		
		TIM_TimeBaseStructure.TIM_Prescaler= 71;										/* 72 - 1 */
		TIM_TimeBaseStructure.TIM_Period = 9999;										/* 10000 - 1 */
		break;
		
	case INTERRUPT_FREQ_100MUS: 
		
		TIM_TimeBaseStructure.TIM_Prescaler= 729;										/* 720 - 1 */
		TIM_TimeBaseStructure.TIM_Period = 9999;										/* 10000 - 1 */
		break;

	default:
		return 0;		
	}		
		
		/* 设置TIM6CLK 为 72MHZ */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);
    //TIM_DeInit(TIM6);
	
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	
    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
		
    TIM_Cmd(TIM6, ENABLE);																		
    
		TIM_ARRPreloadConfig(TIM6, ENABLE);
		
		return 1;
}
/*********************************************END OF FILE**********************/
