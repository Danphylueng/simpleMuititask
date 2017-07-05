#ifndef TIME_TEST_H
#define TIME_TEST_H

#include "stm32f10x.h"

#define INTERRUPT_FREQ_1US (0x01 << 0)    					/* 1us generate a interrupt */
#define INTERRUPT_FREQ_10US (0x01 << 1)							/* :10us generate a interrupt */
#define INTERRUPT_FREQ_100US (0x01 << 2)						/* :100us geretate a interrupt */
#define INTERRUPT_FREQ_1MS (0x01 << 3)		  				/* :1ms generate a interrupt */
#define INTERRUPT_FREQ_10MS (0x01 << 4)  						/* :10ms generate a inrerrupt */
#define INTERRUPT_FREQ_100MUS (0x01 << 5)						/* :100ms genetate a interrupt */

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
u8 TIM6_Configuration(u32 interrupt_freq);

void TIM6_NVIC_Configuration(void);

#endif	/* TIME_TEST_H */
