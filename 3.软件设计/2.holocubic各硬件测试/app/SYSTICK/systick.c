#include "systick.h"

//2^24-1����100000����time���ܳ�100000����100k
void delay_us(u32 time)
{
	SysTick->LOAD = time*168;		//AHBΪ168M��time*168����0����1us
	SysTick->CTRL = (0x04|0x01);	//ѡ��AHB��Ϊsystick�����ð˷�Ƶ��ʹ�ܼ�����
	SysTick->VAL=0;
	//��16λΪ0����ѭ����Ϊ1ʱ���������ɣ��˳�ѭ�����Զ�����ñ�־
	while((SysTick->CTRL&(1<<16)) == 0);
	SysTick->CTRL=0;
	SysTick->VAL=0;		
}

//����delay_us(time*1000)��ʹtime���ܳ���100��������
void delay_ms(u32 time)
{
	for(u32 i = 0; i < time; i++)
		delay_us(1000);
}

