#include "holocubic_function.h"
#include "lcd.h"
#include "systick.h"
#include "esp8266.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "mpu6050.h"
#include "math.h"
#include "led.h"
#include "usart.h"
#include "init.h"
#include "flash.h"
extern u32 msTicks;
extern lv_indev_t * indev_encoder;
extern TimeStruct time;
extern lv_indev_state_t encoder_state;
extern lv_ui_functionClock lv_gui_functionClock;
extern lv_ui_selectFunction lv_gui_selectFunction;
extern u8 nowIsDeskop;
extern u8 nowIsSelectFunction;
extern float initPitch,initRoll,initYaw;
extern float Pitch,Roll,Yaw;
extern u8 isAttitudeRecoveried;
u16 clockFunctionYear;
u8 clockFunctionMonth,clockFunctionDay;
u8 clockFunctionIsAm,clockFunctionHour,clockFunctionMin;
u8 clockFunctionOffOn = SWITCH_OFF;

void clockFunction(void)
{
	if(clockFunctionOffOn == SWITCH_OFF)	//δ�������ӣ����ȡ��ǰʱ�丳ֵ���������С���������ϴ�����ֵ
	{
		clockFunctionYear = time.year;
		clockFunctionMonth = time.month;
		clockFunctionDay = time.day;
		clockFunctionHour = time.hour;
		clockFunctionMin = time.minute;
		if(clockFunctionHour < 12)	clockFunctionIsAm = CLOCK_AM;
		else
		{
			clockFunctionIsAm = CLOCK_PM;
			clockFunctionHour -= 12;
		}
	}
	setup_ui_functionClock(&lv_gui_functionClock);
	u8 nowDropdownSelect = 0;
	u8 nowDropdownIsOpen = 0;
	lv_obj_t *lvWidgetPointerArr[7] = {
		lv_gui_functionClock.screen_date_year_dropdown,
		lv_gui_functionClock.screen_date_month_dropdown,
		lv_gui_functionClock.screen_date_day_dropdown,
		lv_gui_functionClock.screen_am_pm_dropdown,
		lv_gui_functionClock.screen_hour_dropdown,
		lv_gui_functionClock.screen_min_dropdown,
		lv_gui_functionClock.screen_switch_on_off
	};
	lv_obj_t **lvWidgetPointer = lvWidgetPointerArr;
	lv_obj_add_state(lvWidgetPointer[0],LV_STATE_FOCUS_KEY);
	
	while(1)
	{

		lv_task_handler();
		static u32 lastMsTicks = 0;
		if(msTicks - lastMsTicks >= MPU6050_TASK_TIME)	//ÿ100ms���һ�νǶ�
		{
			lv_obj_clear_state(lvWidgetPointer[6],LV_STATE_FOCUS_KEY);
			MPU6050_DMP_Task();
			lastMsTicks = msTicks;
			if((Pitch - initPitch) > MPU6050_TURN_ANGLE && isAttitudeRecoveried)
			{
				isAttitudeRecoveried = 0;
				if(nowDropdownIsOpen == 0)	//��������رգ���ֱ���˳�Ӧ��
				{
					nowIsSelectFunction = 1;
					setup_ui_selectFunction(&lv_gui_selectFunction);
					return;
				}
				else	//����������ѡ
				{
					lv_dropdown_close(*lvWidgetPointer);
					nowDropdownSelect = lv_dropdown_get_selected(*lvWidgetPointer);
					if((nowDropdownSelect-1) >= 0)
					{
						nowDropdownSelect--;
						lv_dropdown_set_selected(*lvWidgetPointer,nowDropdownSelect);
					}
					lv_dropdown_open(*lvWidgetPointer);
				}
			}		
			else if((Pitch - initPitch) < -MPU6050_TURN_ANGLE && isAttitudeRecoveried)
			{
				isAttitudeRecoveried = 0;
				if(*lvWidgetPointer != lv_gui_functionClock.screen_switch_on_off)
				{
					if(nowDropdownIsOpen == 0)	//��������رգ����
					{
						lv_dropdown_open(*lvWidgetPointer);
						lv_dropdown_set_selected_highlight(*lvWidgetPointer,ENABLE);
						nowDropdownIsOpen = 1;
					}
					else	//����������ѡ
					{
						lv_dropdown_close(*lvWidgetPointer);
						nowDropdownSelect = lv_dropdown_get_selected(*lvWidgetPointer);
						if((nowDropdownSelect+1) <= (lv_dropdown_get_option_cnt(*lvWidgetPointer)-1))
						{
							nowDropdownSelect++;
							lv_dropdown_set_selected(*lvWidgetPointer,nowDropdownSelect);
						}
						lv_dropdown_open(*lvWidgetPointer);
					}
					
				}
				else
				{
					nowIsSelectFunction = 1;
					setup_ui_selectFunction(&lv_gui_selectFunction);
					return;
				}
			}			
			else if((Roll - initRoll) > MPU6050_TURN_ANGLE && isAttitudeRecoveried)	
			{
				isAttitudeRecoveried = 0;
				if(*lvWidgetPointer != lv_gui_functionClock.screen_switch_on_off)
				{
					lv_dropdown_close(*lvWidgetPointer);	nowDropdownIsOpen = 0;
					lv_obj_clear_state(*lvWidgetPointer,LV_STATE_FOCUS_KEY);
					lvWidgetPointer++;
					lv_obj_add_state(*lvWidgetPointer,LV_STATE_FOCUS_KEY);
				}
				else
				{				
					clockFunctionOffOn = SWITCH_ON;
					lv_obj_add_state(*lvWidgetPointer, LV_STATE_CHECKED);	
					clockFunctionYear = lv_dropdown_get_selected(lv_gui_functionClock.screen_date_year_dropdown)+2022;;	//��������ʱ��
					clockFunctionMonth = lv_dropdown_get_selected(lv_gui_functionClock.screen_date_month_dropdown)+1;
					clockFunctionDay = lv_dropdown_get_selected(lv_gui_functionClock.screen_date_day_dropdown)+1;
					clockFunctionHour = lv_dropdown_get_selected(lv_gui_functionClock.screen_hour_dropdown);
					clockFunctionMin = lv_dropdown_get_selected(lv_gui_functionClock.screen_min_dropdown);
					if(lv_dropdown_get_selected(lv_gui_functionClock.screen_am_pm_dropdown) == 0)
						clockFunctionIsAm = CLOCK_AM;
					else
						clockFunctionIsAm = CLOCK_PM;
				}
			}
			else if((Roll - initRoll) < -MPU6050_TURN_ANGLE && isAttitudeRecoveried)	
			{
				isAttitudeRecoveried = 0;
				if(*lvWidgetPointer == lv_gui_functionClock.screen_switch_on_off)
				{
					clockFunctionOffOn = SWITCH_OFF;
					lv_obj_clear_state(*lvWidgetPointer, LV_STATE_CHECKED);
				}		
				else if(*lvWidgetPointer != lv_gui_functionClock.screen_date_year_dropdown)
				{
					lv_dropdown_close(*lvWidgetPointer);	nowDropdownIsOpen = 0;
					lv_obj_clear_state(*lvWidgetPointer,LV_STATE_FOCUS_KEY);
					lvWidgetPointer--;
					lv_obj_add_state(*lvWidgetPointer,LV_STATE_FOCUS_KEY);
				}
		
			}
			else if( (fabs(initPitch - Pitch) < MPU6050_RETURN_ANGLE) && (fabs(initRoll - Roll) < MPU6050_RETURN_ANGLE))
				isAttitudeRecoveried = 1;
			printf("isRecoveried = %d\r\n",isAttitudeRecoveried);
		}
		
	}
}

void clockRuningTask(void)
{
	static u8 clockIsArrived = 0;
	if(clockFunctionOffOn == SWITCH_ON)
	{
//		printf("\r\nclockFunctionYear = %d time.year = %d\r\n",clockFunctionYear,time.year);
//		printf("clockFunctionMonth = %d time.month = %d\r\n",clockFunctionMonth,time.month);
//		printf("clockFunctionDay = %d time.day = %d\r\n",clockFunctionDay,time.day);
//		printf("clockFunctionIsAm = %d\r\n",clockFunctionIsAm);
//		printf("clockFunctionHour = %d time.hour = %d\r\n",clockFunctionHour,time.hour);
		if(clockFunctionYear == time.year && clockFunctionMonth == time.month && clockFunctionDay == time.day)
		{
			if(clockFunctionIsAm == CLOCK_AM)
			{
				if(clockFunctionHour == time.hour && clockFunctionMin == time.minute)
				{
					clockIsArrived = 1;
					clockFunctionOffOn = SWITCH_OFF;
				}
			}
			else if(clockFunctionIsAm == CLOCK_PM)
			{
				if(clockFunctionHour == (time.hour-12) && clockFunctionMin == time.minute)
				{
					clockIsArrived = 1;
					clockFunctionOffOn = SWITCH_OFF;
				}
			}
		}
	}
	static u8 cnt = 0;
	static u32 lastMsTicks = 0;
	if(clockIsArrived == 1 && msTicks - lastMsTicks >=1000)	//RGB�л���ɫ��������
	{
		switch (cnt)	
		{
			case 0:
				RGB_OFF();
				RGB_OPEN(RGB_R);
				cnt++;
				break;
			case 1:
				RGB_OFF();
				RGB_OPEN(RGB_G);
				cnt++;
				break;
			case 2:
				RGB_OFF();
				RGB_OPEN(RGB_B);
				cnt++;
				break;
			case 3:
				RGB_OFF();
				clockIsArrived = 0;
				cnt = 0;
				break;
		}	
		lastMsTicks = msTicks;
	}
}


/*
���һ֡240*130�ĵ�����ʾ��ͼ����ÿ��������16λ����
�����СΪ240*130*2��δ����DMAһ�δ���65535���ֽڼ���
*/
#define PROJECTION_DATA_SIZE	(240*130*2)
u8 projectionData[PROJECTION_DATA_SIZE];	
extern u8 DMA2_COMPLETED_LCD;
extern u8 DMA2_COMPLETED_USART;

void projectionFunction(void)	
{
	LCD_FullColor(BLACK);
	u8 flag = 0;	//flag = 0ʱ�����ʱ���Զ�ȡ��֡��flag = 1ʱ�����ʱ����д��֡
	printf_Init(PROJECTION_BAUD_RATE);	//����ΪͶ��������
	while(1)
	{
		if(DMA2_COMPLETED_USART == 1 && DMA2_COMPLETED_LCD == 1)	//��DMA����
		{
			if(flag == 0)	//��ȡ1֡
			{
				USART1DMA_Init(projectionData,PROJECTION_DATA_SIZE);
				DMA_ITConfig(DMA2_Stream5,DMA_IT_TC,ENABLE);
				USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
				DMA2_COMPLETED_USART = 0;	
				flag = 1;
			}
			else if(flag == 1)	//ˢ��1֡
			{
				SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,DISABLE);
				DMA_ITConfig(DMA2_Stream3,DMA_IT_TC,DISABLE);
				LCD_AddressSet(0,239,0+30,129+30);
				LCD_DC_UP;
				LCD_CS_DOWN;	
				SPI1DMA_Init(projectionData,PROJECTION_DATA_SIZE);
				DMA_ITConfig(DMA2_Stream3,DMA_IT_TC,ENABLE);
				SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);
				DMA2_COMPLETED_LCD = 0;
				flag = 0;
			}
		}	
		
		if(DMA2_COMPLETED_USART == 0 || DMA2_COMPLETED_LCD==0)	//����CPU�Ŀ���ʱ������̬
		{
			MPU6050_DMP_Task();
			if((Pitch - initPitch) > MPU6050_TURN_ANGLE)
			{
				//ǿ�Ʊ��DMA����������PC�˴�����;����holocubic�˳���
				//�´��ٽ���ù��ܣ�����ִ����쳣
				DMA2_COMPLETED_USART = 1;
				DMA2_COMPLETED_LCD = 1;
				printf_Init(PRINTF_BAUD_RATE);	//����������������
				nowIsDeskop = 0;
				nowIsSelectFunction = 1;
				setup_ui_selectFunction(&lv_gui_selectFunction);
				return;
			}
		}
		
	}
}



/*
	�������¸�ʽ�ַ����ɸ��£����С�wifi�˺š�����
	city=guangzhou;
	wifi=xx;
	password=xx;
	��ע����ӷֺţ�ÿ�������赥��ʹ�á�Ϊ�����ַ������쳣��wifi���õ��˺������벻Ҫ�зֺţ�
*/
lv_ui_functionSet lv_gui_functionSet;
lv_ui_functionSetLoading lv_gui_functionSetLoading;
extern CityWifiInfo_t cityWifiInfo;
extern WeatherStruct nowWeather;
char wifiStr[50] = {0},cityStr[50] = {0},passwordStr[50] = {0};
u8 len = 0,flagEqual = 0,flagEnd = 0;
u32 lastRecvMsTicks = 0,lastIMUmsTicks = 0;
char cityNameArrPinYin[][10] = {"shenzhen","zhanjiang","guangzhou","ganzhou","nanchang","beijing","shanghai"}; 
char cmdStr[255] = {0},tempStr[255] = {0};
u8 setFunctionUpdateWeather = 1;
/********************************************************/
/********************************************************/

void setFunction(void)
{

	u8 cityNumArr[3] = {cityWifiInfo.cityNum,strlen(cityWifiInfo.wifiName),strlen(cityWifiInfo.wifiPassword)};
	u8 cityIsChanged = 0,wifiIsChanged = 0,passwordIsChanged = 0;
	
	setup_ui_functionSet(&lv_gui_functionSet);
	updateSetFunctionCity(cityWifiInfo.cityName);
	updateSetFunctionWifiName(cityWifiInfo.wifiName);
	updateSetFunctionWifiPassword(cityWifiInfo.wifiPassword);
	printf("\r\nPlease enter command:\r\n");
	printf("city=xxx;\r\n");printf("wifi=xxx;\r\n");printf("password=xxx;\r\n");
	
	
	while((Pitch - initPitch) < MPU6050_TURN_ANGLE)
	{
		lv_task_handler();
		if(msTicks - lastIMUmsTicks >= MPU6050_TASK_TIME)	//��̬�������
		{
			MPU6050_DMP_Task();
			lastIMUmsTicks = msTicks;
		}
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
		{
			lastRecvMsTicks = msTicks;
			cmdStr[len++] = USART_ReceiveData(USART1);
			if(cmdStr[len-1] == '\r'||cmdStr[len-1]=='\n')	//Ϊ������ѡ��������ġ��������С������û��з����������ַ���
					len--;
			if(len == 255)
			{
				memset(cmdStr,0,sizeof(cmdStr));
				flagEqual = 0;	flagEnd = 0;	len = 0;
				printf("Command too long!\r\n");
			}			
			else if(cmdStr[len-1] == '=')
				flagEqual = 1;
			else if(cmdStr[len-1] == ';' && flagEqual == 1)	//���ҵ��˵Ⱥţ����ҵ��˷ֺţ�˵���ѽ��յ�һ������
				flagEnd = 1;
		}
		if((len !=0) && (msTicks-lastRecvMsTicks > 1000) && (flagEnd == 0))	//���������δ��ɣ���1s��δ���յ��ַ�����Ϊ��Ч����
		{
			if(strcmp(cmdStr,"exit") == 0)	//ǿ���˳�
			{
				nowIsDeskop = 0;
				nowIsSelectFunction = 1;
				setup_ui_selectFunction(&lv_gui_selectFunction);
				return;	
			}
			printf("Error cmd:%s\r\nPlease enter again\r\n",cmdStr);
			memset(cmdStr,0,sizeof(cmdStr));
			flagEqual = 0;	flagEnd = 0;	len = 0;
		}
		if(flagEnd == 1)
		{
			memset(tempStr,0,sizeof(tempStr));
			for(int i = 0; (i < len)&&(cmdStr[i] != '='); i++)	//���ݵȺ�ǰ���ַ�����������������
				tempStr[i] = cmdStr[i];
			if(strcmp(tempStr,"city") == 0)
			{
				memset(cityStr,0,sizeof(cityStr));
				for(int i = 5; cmdStr[i]!=';';i++)
					cityStr[i-5] = cmdStr[i];
			
				int pos = -1;
				for(u8 i = 0; i < 10; i++)										//Ѱ�Ҹó��ж�Ӧ���±�
					if(strcmp(cityStr,cityNameArrPinYin[i])==0)
						pos = i;
					
				if(pos == -1)
					printf("\r\nNo city:%s��\r\n",cityStr);
				else
				{
					cityNumArr[0] = pos;		//����д��flash������
					cityWifiInfo.cityNum = pos;	//����ȫ�ֳ����±�
					strcpy(cityWifiInfo.cityName,cityStr);	//����ȫ�ֳ���ƴ��
					updateSetFunctionCity(cityWifiInfo.cityName);	//���½���ĳ�����

					cityIsChanged = 1;
					printf("Update city:%s\r\n",cityWifiInfo.cityName);
				}	
			}
			else if(strcmp(tempStr,"wifi") == 0)
			{
				memset(wifiStr,0,sizeof(wifiStr));
				for(int i = 5; cmdStr[i]!=';';i++)
					wifiStr[i-5] = cmdStr[i];
				strcpy(cityWifiInfo.wifiName,wifiStr);
				updateSetFunctionWifiName(cityWifiInfo.wifiName);
				
				cityNumArr[1] = strlen(cityWifiInfo.wifiName);
				wifiIsChanged = 1;
				printf("Update wifi:%s\r\n",cityWifiInfo.wifiName);	
			}
			else if(strcmp(tempStr,"password") == 0)
			{
				memset(passwordStr,0,sizeof(passwordStr));
				for(int i = 9; cmdStr[i]!=';';i++)
					passwordStr[i-9] = cmdStr[i];
				strcpy(cityWifiInfo.wifiPassword,passwordStr);
				updateSetFunctionWifiPassword(cityWifiInfo.wifiPassword);
				
				cityNumArr[2] = strlen(cityWifiInfo.wifiPassword);
				passwordIsChanged = 1;
				printf("Update password:%s\r\n",cityWifiInfo.wifiPassword);
			}
			else
				printf("Error cmd:%s\r\nPlease enter again",cmdStr);
			memset(cmdStr,0,sizeof(cmdStr));
			flagEqual = 0;	flagEnd = 0;	len = 0;
		}
	}
	
	
	if(cityIsChanged||wifiIsChanged||passwordIsChanged)
	{

		SPI_DeInit(SPI2);
		SPI2_Init();
		setup_ui_functionSetLoading(&lv_gui_functionSetLoading);
		updateSetLoadingBar(0);

		if(wifiIsChanged||passwordIsChanged)	//������wifi��������wifi�����»�ȡ����������˵��ֻ���˳��У�ֻ���ȡ����
		{
			FLASH_WriteData(45,0,cityNumArr,3);
			if(FLASH_CheckSectorData(45,0,cityNumArr,3) == 0)	
				printf("Flash write error!\r\n");
			
			FLASH_WriteData(45,1,(u8*)cityWifiInfo.wifiName,strlen(cityWifiInfo.wifiName));	
			if(FLASH_CheckSectorData(45,1,(u8*)cityWifiInfo.wifiName,strlen(cityWifiInfo.wifiName)) == 0)
				printf("Flash write error!\r\n");
			
			FLASH_WriteData(45,2,(u8*)cityWifiInfo.wifiPassword,strlen(cityWifiInfo.wifiPassword));
			if(FLASH_CheckSectorData(45,2,(u8*)cityWifiInfo.wifiPassword,strlen(cityWifiInfo.wifiPassword)) == 0)
				printf("Flash write error!\r\n");
			
			updateSetLoadingBar(50);
			for(int i = 0; i < 1000/LV_DISP_DEF_REFR_PERIOD; i++)
			{
				lv_task_handler();	delay_ms(LV_DISP_DEF_REFR_PERIOD);
			}
			
			ESP8266_ConnectWifi();
		}
		FLASH_WriteData(45,0,cityNumArr,3);
		if(FLASH_CheckSectorData(45,0,cityNumArr,3) == 0)	
			printf("Flash write error!\r\n");
		
		updateSetLoadingBar(100);	
		for(int i = 0; i < 1000/LV_DISP_DEF_REFR_PERIOD; i++)
		{
			lv_task_handler();	delay_ms(LV_DISP_DEF_REFR_PERIOD);
		}
		
		nowWeather = ESP8266_GetWeather(cityWifiInfo.cityName);
		setFunctionUpdateWeather = 1;
	}
	
	nowIsDeskop = 0;
	nowIsSelectFunction = 1;
	setup_ui_selectFunction(&lv_gui_selectFunction);
	return;

}

/*
����ͶӰ���ܵ�projectionData���飬ÿ�δ���240*120*2�����ţ�ͼ��
*/
extern u8 DMA1_COMPLETED;
void pictureFunction(void)	
{
	static u32 lastPictureTicks = 0;
	u8 picNum = 0, block = 0, sector = 0;
	LCD_FullColor(BLACK);
	while((Pitch - initPitch) < MPU6050_TURN_ANGLE)
	{
		MPU6050_DMP_Task();
		if(msTicks - lastPictureTicks > 50)
		{
			lastPictureTicks = msTicks;
			block = 46 + 2*picNum;
			FLASH_DMAReadData(block,sector,projectionData,57600);
			while(DMA1_COMPLETED == 0);	DMA1_COMPLETED = 0;
			LCD_DMAWriteHalfFrame(projectionData,57600,0,239,0,119);
			
			block++;
			FLASH_DMAReadData(block,sector,projectionData,57600);
			while(DMA1_COMPLETED == 0);	DMA1_COMPLETED = 0;
			LCD_DMAWriteHalfFrame(projectionData,57600,0,239,120,239);
			
			picNum++;
			if(picNum == 40)
				picNum = 0;
		}
	}
	nowIsDeskop = 0;
	nowIsSelectFunction = 1;
	setup_ui_selectFunction(&lv_gui_selectFunction);
	return;
	
}




