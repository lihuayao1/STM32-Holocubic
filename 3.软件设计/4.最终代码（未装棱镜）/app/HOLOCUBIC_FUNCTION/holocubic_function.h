#ifndef _HOLOCUBIC_FUNCTION_H
#define _HOLOCUBIC_FUNCTION_H

#include "stm32f4xx.h"

#define CLOCK_AM	1
#define CLOCK_PM 0
#define SWITCH_ON	1
#define SWITCH_OFF	0
void clockFunction(void);
void clockRuningTask(void);
void projectionFunction(void);
void setFunction(void);
#endif

