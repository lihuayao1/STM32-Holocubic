#include "esp8266.h"
#include "usart.h"
#include "string.h"
#include "gui_guider.h"
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
	
	ESP8266_ConnectWifi();	//连接wifi
	
	TimeStruct time;				//连接时间
	do{
		ESP8266_SendString("AT+CIPSNTPCFG=1,8",100,ESP8266_NO_PROCESS_RETURN_DATA);
		time = ESP8266_GetTime();
	}while(time.year == 1970);	//首次获取时间可能误识别为1970年，等待读取正确即可
	
	WeatherStruct weather;	//连接天气
	ESP8266_SendString("AT+CIPSTART=\"TCP\",\"api.seniverse.com\",80",500,ESP8266_NO_PROCESS_RETURN_DATA);
}




extern u8 usart2RecvData[500];
extern u32 usart2Pos;
extern u32 msTicks;
u32 USART2_RecvCompleteTime;	//接收完成时的msTicks
void ESP8266_SendString(char sendStr[150],u32 waitms,u8 needProcessData)	//待发送字符串、接收返回数据的时间、是否需要处理返回数据
{
	//printf("sendStr:%s",sendStr);
	while(*sendStr != '\0')
	{
		USART_SendData(USART2,*sendStr);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);		
		sendStr++;
	}
	USART_SendData(USART2,'\r');	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);		
	USART_SendData(USART2,'\n');	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);		
	USART2_RecvCompleteTime = msTicks + waitms;
	while(msTicks != USART2_RecvCompleteTime);	//等时间到达，才能读取字符串
	usart2Pos = 0;	//接收结束，缓冲数组的指针归零
	printf("recv:%s\r\n",usart2RecvData);
	if(needProcessData == ESP8266_NO_PROCESS_RETURN_DATA)	//若不需要处理返回数据则直接清空，否则由函数外部处理完数据再清空
		memset(usart2RecvData,0,sizeof(usart2RecvData));
}

void ESP8266_ExitDataTransfer(void)	//退出透传
{
	USART_SendData(USART2,'+');	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	
	USART_SendData(USART2,'+');	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2,'+');	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

u8 ESP8266_Test(void)
{
	ESP8266_SendString("AT",5000,ESP8266_NO_PROCESS_RETURN_DATA);
	if(strstr((char*)usart2RecvData,"OK")!=NULL)
		return 1;
	else
		return 0;
}


u8 wifiState = WIFI_NOCONNECT;
//char wifiName[50] = "li";	//wifi名
//char wifiPassword[50] = "lihuayao";	//wifi密码
extern char wifiName[];
extern char wifiPassword[];
void ESP8266_ConnectWifi(void)
{
	ESP8266_SendString("AT+CWMODE=1",50,ESP8266_NO_PROCESS_RETURN_DATA);
	//ESP8266_SendString("AT+RST",5000);
	char wifiStr[200] = "AT+CWJAP_DEF=\"";
	strcat(wifiStr,wifiName);	strcat(wifiStr,"\",\"");
	strcat(wifiStr,wifiPassword);	strcat(wifiStr,"\"");
	ESP8266_SendString(wifiStr,5000,ESP8266_NO_PROCESS_RETURN_DATA);	
	if(strstr((char*)usart2RecvData,"WIFI CONNECTED")!=NULL)	//表明wifi成功连接
		wifiState = WIFI_CONNECTED;
}
TimeStruct ESP8266_GetTime(void)	//从返回的字符串解析出时间
{
	TimeStruct ESP8266_Time;
	char weekStr[8][3] = {" ","Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
	char monthStr[13][3] = {" ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	
	ESP8266_SendString("AT+CIPSNTPTIME?",10,ESP8266_PROCESS_RETURN_DATA);
	char *timeStr = strstr((char*)usart2RecvData,":");	timeStr++;
	ESP8266_Time.day = (timeStr[8]-'0')*10 + (timeStr[9]-'0');
	ESP8266_Time.hour = (timeStr[11]-'0')*10 + (timeStr[12]-'0');
	ESP8266_Time.minute = (timeStr[14]-'0')*10 + (timeStr[15]-'0');
	ESP8266_Time.second = (timeStr[17]-'0')*10 + (timeStr[18]-'0');
	ESP8266_Time.year = (timeStr[20]-'0')*1000 + (timeStr[21]-'0')*100 + (timeStr[22]-'0')*10 + (timeStr[23]-'0');
	
	char tempStr[3] = {0};	
	for(u8 i = 0; i < 3; i++)	tempStr[i] =  timeStr[i];	//获取星期字符串
	for(u8 i = 1; i <= 7; i++)
		for(u8 j = 0; j < 3; j++)
			if(tempStr[j]!=weekStr[i][j])
				break;
			else if(j==2 && tempStr[j]==weekStr[i][j])
				ESP8266_Time.week = i;
	
	for(u8 i = 0; i < 3; i++)	tempStr[i] =  timeStr[i+4];	//获取月份字符串
	for(u8 i = 1; i <= 12; i++)
		for(u8 j = 0; j < 3; j++)
		if(tempStr[j]!=monthStr[i][j])
			break;
		else if(j==2 && tempStr[j]==monthStr[i][j])
			ESP8266_Time.month = i;
	memset(usart2RecvData,0,sizeof(usart2RecvData));
//	ESP8266_PrintTime(ESP8266_Time);		
	return ESP8266_Time;
}

void ESP8266_PrintTime(TimeStruct time)
{
	printf("year = %d, month = %d, day = %d, hour = %d, minute = %d, second = %d, week = %d",
		time.year,time.month,time.day,time.hour,time.minute,time.second,time.week);
}
WeatherStruct ESP8266_GetWeather(char *city)
{
	WeatherStruct weather;
	ESP8266_SendString("AT+CIPMODE=1",10,ESP8266_NO_PROCESS_RETURN_DATA);
	ESP8266_SendString("AT+CIPSEND",10,ESP8266_NO_PROCESS_RETURN_DATA);
	char weatherAPIStr[150] = "GET https://api.seniverse.com/v3/weather/now.json?key=SdimjsWV7RGwycVMU&location=";
	strcat(weatherAPIStr,city);	strcat(weatherAPIStr,"&language=en&unit=c");		
	ESP8266_SendString(weatherAPIStr,200,ESP8266_PROCESS_RETURN_DATA);
	ESP8266_ExitDataTransfer();
	char *tempStr = (char*)usart2RecvData;
	tempStr = strstr(tempStr,"text");
	memset(weather.text,0,sizeof(weather.text));
	for(u8 i = 0; tempStr[i+7]!='"'; i++)	//获取天气文本
		weather.text[i] = tempStr[i+7];
	tempStr = strstr(tempStr,"code");
	weather.code = (tempStr[7]-'0')*10 + (tempStr[8]-'0');	//获取天气代码
	tempStr = strstr(tempStr,"ture");
	weather.temperature = (tempStr[7]-'0')*10 + (tempStr[8]-'0');	//获取温度
	memset(usart2RecvData,0,sizeof(usart2RecvData));
	return weather;
}

void ESP8266_PrintWeather(WeatherStruct weather)
{
	printf("text:%s,code:%d,temperature:%d\r\n",weather.text,weather.code,weather.temperature);
}
/*
时间：AT+CIPSNTPTIME?
天气：AT+CIPSTART=”TCP”,”api.seniverse.com”,80。进透传
		 发送https://api.seniverse.com/v3/weather/now.json?key=SdimjsWV7RGwycVMU&location=beijing&language=zh-Hans&unit=c
*/
extern u32 msTicks,t1,t2; 
void ESP8266_Task(void)	//时间，天气获取任务
{
	TimeStruct time = ESP8266_GetTime();
	WeatherStruct weather = ESP8266_GetWeather("zhanjiang");
	ESP8266_PrintTime(time);
	ESP8266_PrintWeather(weather);
}


extern lv_ui lv_gui_deskop;
void ESP8266_UpdateTimeToLCD(void)
{
	char temp[10];
	TimeStruct time = ESP8266_GetTime();
	if(time.second >= 58)	//秒数即将导致其它时间更新时，才考虑更新其它，节省运算资源
	{
		numToString(time.hour,temp);
		lv_label_set_text(lv_gui_deskop.screen_hour,temp);
		numToString(time.minute,temp);
		lv_label_set_text(lv_gui_deskop.screen_min,temp);
		if(time.hour >=23 && time.minute == 59)	//即将更新日期
		{
			char strMonthDay[10],strWeek[10];
			memset(strMonthDay,0,sizeof(strMonthDay));
			numToString(time.month,temp);	strcat(strMonthDay,temp);	strcat(strMonthDay,"月");
			numToString(time.day,temp);	strcat(strMonthDay,temp);	strcat(strMonthDay,"日");
			lv_label_set_text(lv_gui_deskop.screen_date,strMonthDay);
			
			char weekNumToChinese[8][5]={
			" ","一","二","三","四","五","六","日"};
			memset(strWeek,0,sizeof(strWeek));
			////////////
			strcat(strWeek,"星期");
		}
	}
	numToString(time.second,temp);
	lv_label_set_text(lv_gui_deskop.screen_second,temp);

	
}



