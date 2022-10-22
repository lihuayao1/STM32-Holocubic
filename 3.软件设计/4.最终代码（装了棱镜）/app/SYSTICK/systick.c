#include "systick.h"

//2^24-1不到100000，故time不能超100000，即100k
void delay_us(u32 time)
{
	SysTick->LOAD = time*168;		//AHB为168M，time*168减到0代表1us
	SysTick->CTRL = (0x04|0x01);	//选用AHB作为systick，不用八分频；使能计数器
	SysTick->VAL=0;
	//第16位为0则死循环，为1时代表计数完成，退出循环，自动清除该标志
	while((SysTick->CTRL&(1<<16)) == 0);
	SysTick->CTRL=0;
	SysTick->VAL=0;		
}

//若用delay_us(time*1000)会使time不能超过100，不好用
void delay_ms(u32 time)
{
	for(u32 i = 0; i < time; i++)
		delay_us(1000);
}

