#include "esp8266.h"
#include "usart.h"
#include "string.h"
#include "gui_guider.h"
#include "custom.h"
#include "systick.h"
#include "stdlib.h"
#include "init.h"
WeatherStruct nowWeather;
extern u8 usart2RecvData[500];
extern u8 usart2pos;
extern TimeStruct time;
extern CityWifiInfo_t cityWifiInfo;
void ESP8266_Init(void)
{
		/**********ESP8266����2************/
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
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	//IO0��RST��©���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);
	
	ESP8266_ConnectWifi();	//����wifi
	delay_ms(200);	//wifi���ӳɹ�����ȴ�ESP8266����һ��ʱ��
	
	do{											//��ȡʱ��
		ESP8266_SendString("AT+CIPSNTPCFG=1,8",100,ESP8266_NO_PROCESS_RETURN_DATA);
		time = ESP8266_GetTime();
		delay_ms(100);
	}while(time.year == 1970);	//�״λ�ȡʱ�������ʶ��Ϊ1970�꣬�ȴ���ȡ��ȷ����
	
	
	nowWeather = ESP8266_GetWeather(cityWifiInfo.cityName);
}





extern u32 usart2Pos;
extern u32 msTicks;
u32 USART2_RecvCompleteTime;	//�������ʱ��msTicks
void ESP8266_SendString(char sendStr[150],u32 waitms,u8 needProcessData)	//�������ַ��������շ������ݵ�ʱ�䡢�Ƿ���Ҫ����������
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
	while(msTicks != USART2_RecvCompleteTime);	//��ʱ�䵽����ܶ�ȡ�ַ���
	printf("recv:%s\r\n",usart2RecvData);
	if(needProcessData == ESP8266_NO_PROCESS_RETURN_DATA)	//������Ҫ������������ֱ����գ������ɺ����ⲿ���������������
	{	memset(usart2RecvData,0,sizeof(usart2RecvData));	usart2Pos = 0;}
}

void ESP8266_ExitDataTransfer(void)	//�˳�͸��
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
void ESP8266_ConnectWifi(void)
{
	ESP8266_SendString("AT+CWMODE=1",50,ESP8266_NO_PROCESS_RETURN_DATA);
	//ESP8266_SendString("AT+RST",5000);
	char wifiStr[200] = "AT+CWJAP_DEF=\"";
	strcat(wifiStr,cityWifiInfo.wifiName);	strcat(wifiStr,"\",\"");
	strcat(wifiStr,cityWifiInfo.wifiPassword);	strcat(wifiStr,"\"");
	ESP8266_SendString(wifiStr,100,ESP8266_PROCESS_RETURN_DATA);	
	while(strstr((char*)usart2RecvData,"OK")==NULL);
	memset(usart2RecvData,0,sizeof(usart2RecvData));usart2Pos = 0;
	wifiState = WIFI_CONNECTED;
//	if(strstr((char*)usart2RecvData,"WIFI CONNECTED")!=NULL)	//����wifi�ɹ�����
//		wifiState = WIFI_CONNECTED;
}
TimeStruct ESP8266_GetTime(void)	//�ӷ��ص��ַ���������ʱ��
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
	for(u8 i = 0; i < 3; i++)	tempStr[i] =  timeStr[i];	//��ȡ�����ַ���
	for(u8 i = 1; i <= 7; i++)
		for(u8 j = 0; j < 3; j++)
			if(tempStr[j]!=weekStr[i][j])
				break;
			else if(j==2 && tempStr[j]==weekStr[i][j])
				ESP8266_Time.week = i;
	
	for(u8 i = 0; i < 3; i++)	tempStr[i] =  timeStr[i+4];	//��ȡ�·��ַ���
	for(u8 i = 1; i <= 12; i++)
		for(u8 j = 0; j < 3; j++)
		if(tempStr[j]!=monthStr[i][j])
			break;
		else if(j==2 && tempStr[j]==monthStr[i][j])
			ESP8266_Time.month = i;
	memset(usart2RecvData,0,sizeof(usart2RecvData));usart2Pos = 0;
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
	
	ESP8266_SendString("AT+CIPSTART=\"TCP\",\"api.seniverse.com\",80",100,ESP8266_PROCESS_RETURN_DATA);	//��һ��ʱ����ܵ��ߣ�������
	while(strstr((char*)usart2RecvData,"CONNECT")==NULL);	//����connect��already connected�����Լ�������
	memset(usart2RecvData,0,sizeof(usart2RecvData));usart2Pos = 0;
	

	ESP8266_SendString("AT+CIPMODE=1",10,ESP8266_NO_PROCESS_RETURN_DATA);
	ESP8266_SendString("AT+CIPSEND",10,ESP8266_NO_PROCESS_RETURN_DATA);
	char weatherAPIStr[150] = "GET https://api.seniverse.com/v3/weather/now.json?key=SdimjsWV7RGwycVMU&location=";
	strcat(weatherAPIStr,city);	strcat(weatherAPIStr,"&language=en&unit=c");		
	ESP8266_SendString(weatherAPIStr,10,ESP8266_PROCESS_RETURN_DATA);
	while(strstr((char*)usart2RecvData,"}]}")==NULL);	//�ȴ����յ�ĩβ�������ţ�������ս���
	char *tempStr = (char*)usart2RecvData;
	tempStr = strstr(tempStr,"code");	tempStr = strstr(tempStr,":");
	char numString[5];	
	memset(numString,0,sizeof(numString));	u8 i = 2;
	while(tempStr[i]!='\"')
	{
		numString[i-2] = tempStr[i];
		i++;
	}
	weather.code = stringToNum(numString);	
	memset(numString,0,sizeof(numString));	i = 2;
	
	tempStr = strstr(tempStr,"ture");	tempStr = strstr(tempStr,":");
	while(tempStr[i]!='\"')
	{
		numString[i-2] = tempStr[i];
		i++;
	}
	weather.temperature = stringToNum(numString);	//��ȡ�¶�
	memset(numString,0,sizeof(numString));	i = 2;
	memset(usart2RecvData,0,sizeof(usart2RecvData));usart2Pos = 0;
	memset(weatherAPIStr,0,sizeof(weatherAPIStr));
	
	delay_ms(200);	//���η���Ӧ����һ�����
	

	strcat(weatherAPIStr,"GET https://api.seniverse.com/v3/weather/daily.json?key=SdimjsWV7RGwycVMU&location=");
	strcat(weatherAPIStr,city);	strcat(weatherAPIStr,"&language=en&unit=c&start=0&days=1");	
	ESP8266_SendString(weatherAPIStr,10,ESP8266_PROCESS_RETURN_DATA);
	while(strstr((char*)usart2RecvData,"}]}")==NULL);usart2Pos = 0;
	ESP8266_ExitDataTransfer();
	tempStr = (char*)usart2RecvData;
	tempStr = strstr(tempStr,"high");	tempStr = strstr(tempStr,":");
	while(tempStr[i]!='\"')
	{
		numString[i-2] = tempStr[i];
		i++;
	}
	weather.highTemperature = stringToNum(numString);	//��ȡ�������
	memset(numString,0,sizeof(numString));	i = 2;
	tempStr = strstr(tempStr,"low");	tempStr = strstr(tempStr,":");
	while(tempStr[i]!='\"')
	{
		numString[i-2] = tempStr[i];
		i++;
	}
	weather.lowTemperature = stringToNum(numString);	//��ȡ�������
	memset(numString,0,sizeof(numString));	i = 2;
	
	tempStr = strstr(tempStr,"rainfall");	tempStr = strstr(tempStr,":");
	while(tempStr[i]!='.')//����С����
	{
		numString[i-2] = tempStr[i];
		i++;
	}
	weather.precipitation = stringToNum(numString);	//��ȡ��ˮ��
	memset(numString,0,sizeof(numString));	i = 2;
	
	tempStr = strstr(tempStr,"humidity");	tempStr = strstr(tempStr,":");
	while(tempStr[i]!='\"')
	{
		numString[i-2] = tempStr[i];
		i++;
	}
	weather.humidityPercent = stringToNum(numString);	//��ȡʪ��	
	
	memset(usart2RecvData,0,sizeof(usart2RecvData));usart2Pos = 0;
	return weather;
}

void ESP8266_PrintWeather(WeatherStruct weather)
{
	printf("code:%d,temperature:%d\r\n",weather.code,weather.temperature);
}
/*
ʱ�䣺AT+CIPSNTPTIME?
������AT+CIPSTART=��TCP��,��api.seniverse.com��,80����͸��
		 ����https://api.seniverse.com/v3/weather/now.json?key=SdimjsWV7RGwycVMU&location=beijing&language=zh-Hans&unit=c
*/
extern u32 msTicks,t1,t2; 
extern u8 setFunctionUpdateWeather;
void ESP8266_Task(void)	//ʱ�䣬������ȡ����
{
	static u32 lastTicks = 0;
	static int lastMinute = -1;	//��ֵ-1����֤�ϵ���ȡ����

	if(msTicks-lastTicks > 500)	//�����ϴθ��´���100ms�������ʱ�䡣������1000ms���ܳ�������һ�η�ҳ2��������
	{
		time = ESP8266_GetTime();
		ESP8266_UpdateTimeToLCD();
		lastTicks = msTicks;
	}	
	static u8 minCnt = 0;
	if(time.minute != lastMinute)
	{
		minCnt++;
		if((minCnt == 10)||(lastMinute == -1))	//10���ӻ�ȡһ������
		{
			minCnt = 0;
			updateDeskopCity(cityWifiInfo.cityName);	
			nowWeather = ESP8266_GetWeather(cityWifiInfo.cityName);
			updateDeskopWeatherText(nowWeather.code);
			updateDeskopTemperature(nowWeather.temperature);
			updateDeskopWeatherPattern(nowWeather.code);
			updateDeskopWeatherInfo(nowWeather.highTemperature,nowWeather.lowTemperature,nowWeather.precipitation,nowWeather.humidityPercent);
		}
		lastMinute = time.minute;
	}
	if(setFunctionUpdateWeather == 1)
	{
		setFunctionUpdateWeather = 0;
		updateDeskopWeatherText(nowWeather.code);
		updateDeskopTemperature(nowWeather.temperature);
		updateDeskopWeatherPattern(nowWeather.code);
		updateDeskopWeatherInfo(nowWeather.highTemperature,nowWeather.lowTemperature,nowWeather.precipitation,nowWeather.humidityPercent);
	}
	
}


extern lv_ui_deskop lv_gui_deskop;
void ESP8266_UpdateTimeToLCD(void)
{
	char temp[10];
	numToString(time.hour,temp);
	lv_label_set_text(lv_gui_deskop.screen_hour,temp);
	numToString(time.minute,temp);
	lv_label_set_text(lv_gui_deskop.screen_min,temp);	
	updateDeskopDate(time.month,time.day,time.week);	//ֻ�ܵ���setup_src_screen�еĺ�������Ϊ�ô��漰����
	numToString(time.second,temp);
	lv_label_set_text(lv_gui_deskop.screen_second,temp);

	
}



