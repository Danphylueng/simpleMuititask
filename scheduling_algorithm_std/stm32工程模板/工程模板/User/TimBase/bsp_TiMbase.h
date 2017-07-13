#ifndef TIME_TEST_H
#define TIME_TEST_H

#include "stm32f10x.h"

void TIM6_NVIC_Configuration(void);
void TIM6_Configuration(void);

/**
 * \brief    :this fuction use to increase the _g_time_val, this fuction is called in TIM IRQ handle fuction
 * \detail   :
 *
 *
 * \retval : none
 */
void time_count(void);

/**
 * \brief get the program run time (millisecond)
 *
 * \retval : return the sys time in ms
 */
uint32_t millis (void);

/**
 * \brief get the timer counter value (millisecond)
 *
 * \retval : return the timer counter
 */
uint32_t get_timer_counter (void);

/**
 * \brief get the program run time (microsecond)
 *
 * \retval : return the sys time in us
 */
uint32_t micros (void);

#endif	/* TIME_TEST_H */
