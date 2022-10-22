#include "tim.h"

void tickTIM_Init()	//系统计时定时器TIM6初始化
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1;	//频率1M
	TIM_TimeBaseStructure.TIM_Period = 1000-1;	//计数1000次即为1ms
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);	//3位主优先级，1位次优先级
	NVIC_InitTypeDef NVIC_InitStructure; 
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//全局优先级最高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM6,ENABLE);
}

extern u32 msTicks;
int get_tick_count(unsigned long *count)
{
	count[0] = msTicks;
	return 0;
}
