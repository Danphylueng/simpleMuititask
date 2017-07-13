/**
  ******************************************************************************
  * @file    bsp_TimBase.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   TIM6 1ms ��ʱӦ��bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "bsp_TiMbase.h" 

__IO u32 g_time_val = 0;													/*!< use to recotd the time (ms), if the system work 50 days this variable will over flow*/

/// TIM6�ж����ȼ�����
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
 * �ж�����Ϊ = 1/(72MHZ /72) * 1000 = 1ms
 *
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIM_Period(ARR) --> �ж� ��TIMxCNT����Ϊ0���¼��� 
 */
void TIM6_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		/* ����TIM6CLK Ϊ 72MHZ */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);
    //TIM_DeInit(TIM6);
	
	/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    TIM_TimeBaseStructure.TIM_Period=1000;
	
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
	  /* ʱ��Ԥ��Ƶ��Ϊ72 */
    TIM_TimeBaseStructure.TIM_Prescaler= 72;
	
		/* ���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ,����û���õ� */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	
    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
		
    TIM_Cmd(TIM6, ENABLE);																		
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , DISABLE);		/*�ȹرյȴ�ʹ��*/    
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
