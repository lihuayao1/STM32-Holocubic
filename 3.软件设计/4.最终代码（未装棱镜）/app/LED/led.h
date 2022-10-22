#ifndef _LED_H
#define _LED_H
#include "stm32f4xx.h"

#define RGB_R	0x01
#define RGB_G	0x02
#define RGB_B	0x04

void LED_Init(void);	//PB1µãµÆ
void LED_ON(void);
void LED_OFF(void);
void RGB_OFF(void);
void RGB_OPEN(u8 RGB_SELECT);
void RGB_Init(void);	//²ÊµÆ
void RGB_Test(void);
#endif
