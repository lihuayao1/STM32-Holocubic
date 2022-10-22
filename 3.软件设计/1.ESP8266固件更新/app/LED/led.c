#include "led.h"
void LED_Init(void)	//PB1µãµÆ
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE); 													   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	LED_OFF();	
}

void LED_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}

void LED_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
}
