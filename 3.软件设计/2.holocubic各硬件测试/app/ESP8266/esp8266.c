#include "esp8266.h"
#include "usart.h"
#include "string.h"
void ESP8266_Init(void)
{
		/**********ESP8266串口2************/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2  ;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	
	USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure); 
  USART_Cmd(USART2, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	/**********************************/	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	//IO0和RST开漏输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);
}

extern u8 usart2RecvData[500];
extern u32 usart2Pos;
extern u32 msTicks;
u32 USART2_RecvCompleteTime;	//接收完成时的msTicks
void ESP8266_SendString(u8* sendStr,u32 waitms)	//待发送字符串、接收返回数据的时间
{
//	printf("send:%s\r\n",sendStr);
//	strcat((char*)sendStr,"\r\n");
	while(*sendStr != '\0')
	{
		USART_SendData(USART2,*sendStr);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);		
		sendStr++;
	}
	USART2_RecvCompleteTime = msTicks + waitms;
	while(msTicks != USART2_RecvCompleteTime);	//等时间到达，才能读取字符串
	usart2Pos = 0;	//接收结束，缓冲数组的指针归零
//	printf("recv:%s\r\n",usart2RecvData);
}

u8 ESP8266_Test(void)
{
	ESP8266_SendString("AT\r\n",5000);
	if(strstr((char*)usart2RecvData,"OK")!=NULL)
		return 1;
	else
		return 0;
}



