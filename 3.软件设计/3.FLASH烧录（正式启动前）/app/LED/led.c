#include "led.h"
#include "systick.h"
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

void RGB_OFF(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
	GPIO_SetBits(GPIOC,GPIO_Pin_7);
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
}

void RGB_OPEN(u8 RGB_SELECT)
{
	if(RGB_SELECT&RGB_R)
		GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	if(RGB_SELECT&RGB_G)
		GPIO_ResetBits(GPIOC,GPIO_Pin_7);
	if(RGB_SELECT&RGB_B)
		GPIO_ResetBits(GPIOC,GPIO_Pin_6);
		
}

void RGB_Init(void)	//²ÊµÆ
{
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOC, ENABLE); 	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	RGB_OFF();
}

void RGB_Test()
{
	RGB_OFF();
	RGB_OPEN(RGB_R);
	delay_ms(1000);
	RGB_OFF();
	RGB_OPEN(RGB_G);
	delay_ms(1000);
	RGB_OFF();
	RGB_OPEN(RGB_B);
	delay_ms(1000);
}




