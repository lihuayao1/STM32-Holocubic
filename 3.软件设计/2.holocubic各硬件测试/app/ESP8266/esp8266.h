#ifndef _ESP8266_H
#define _ESP8266_H
#include "stm32f4xx.h"

void ESP8266_Init(void);
void ESP8266_SendString(u8* sendStr,u32 waitms);	//�������ַ��������շ������ݵ�ʱ��
u8 ESP8266_Test(void);
#endif
