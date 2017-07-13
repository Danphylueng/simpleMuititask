#ifndef _TASK_H
#define _TASK_H

#include "stm32f10x.h"

#define ARRAY_LEN(ARRAY) (sizeof(ARRAY)/sizeof(ARRAY[0]))
	

#ifdef __DEBUG__
#define DE_PRINTF(format,...) printf("File:"__FILE__",Line: %05d: "format"\n",__LINE__,##__VA_ARGS__)
#else
#define DE_PRINTF(format,...)
#endif

typedef struct _task_components
{
    void (*taskhook)(void);       /* pointer to task function */
	uint16_t rate_hz;             /* run rate of task */
	uint16_t max_time_micros;     /* max time could be take */
}task_components;      

void tick(void);
void run(uint16_t time_available);
#endif



