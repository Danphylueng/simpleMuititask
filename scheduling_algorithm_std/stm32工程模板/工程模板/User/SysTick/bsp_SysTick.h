#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"



#define SYSTICK_INT_1MS (SystemCoreClock / 1000)    	/*!< 1ms中断一次 */
#define SYSTICK_INT_10US (SystemCoreClock / 100000)	 	/*!< 10us中断一次 */
#define SYSTICK_INT_1uS (SystemCoreClock / 1000000) 	/*!< 1us中断一次 */

void SysTick_Init(void);
//void Delay_us(__IO u32 nTime);
//#define Delay_ms(x) Delay_us(100*x)	 //单位ms

/**
 * \brief    : increase the conter in this fuction. if ms arrve, set the  time_flag to 1
 * \detail   :
 *
 * \param[in]:none
 *
 * \retval : none
 */
void increase_counter(void);

#endif /* __SYSTICK_H */
