/*****************************************
���ܣ�������������¼�ⲿflash��������GIF�Լ�����ͼ���������

ʹ�÷�����ÿ�α���һ��ע�ͣ�������¼���Σ���ν�Ƭ��FLASH����
				  ��д���ⲿFLASH�����write_flash.c����ÿ��¼һ�Σ���
					��ͨ�������Ļ����ת���ŵ�ͼƬ�Ƿ�����ȷ���Ƿ���¼
					�ɹ���ȫ����¼��ɺ�����ͼ��Ӧ��39�ţ�GIFӦ˳����
					�У��ް�ɫ���֡��

ע�⣺��¼ĳһ�������ݺ������ж�Ӧ��ͼ����ܳ��ְ��ߣ�������
		 ��flashд��ʱ����bug���������ݴ���ֻ������д��ò�����
		 �ݼ��ɡ�
*****************************************/
#include "usart.h"
#include "systick.h"
#include "flash.h"
#include "tim.h"
#include "lcd.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "write_flash.h"
extern u32 msTicks;
lv_ui lv_gui_deskop;
int main()
{
	printf_Init();
	FLASH_Init();
	tickTIM_Init();
	LCD_Init();
	
	
	/****************************************
	��¼������ȡ������ע�Ϳ��Բ����Ƿ���¼�ɹ���
	�˴�Ϊ��һ��ע�͡��ڶ���ע���ڵ���
	****************************************/
//	lv_init();
//	lv_port_disp_init();

//	setup_ui(&lv_gui_deskop);
//	events_init(&lv_gui_deskop);
	/****************************************
	****************************************/
	
	
	
	
	
	writeFlashWeatherPattern();
	writeFlashDancePattern();
	writeFlashCityWifi();
	writeFlash3DPattern();
	int i = 0;
	int j = 0;
	

	
	u8 Info[3];
	char readWifiName[200] = {0};
	char readWifiPassWord[200] = {0};
	FLASH_ReadData(45,0,Info,3);
	FLASH_ReadData(45,1,(u8*)readWifiName,Info[1]);
	FLASH_ReadData(45,2,(u8*)readWifiPassWord,Info[2]);
	printf("cityNum = %d\r\nwifiName = %s\r\nwifiPassword = %s\r\n",Info[0],readWifiName,readWifiPassWord);
	
	u32 weatherLastMsTicks = msTicks;
	u32 danceLastMsTicks = msTicks;
	while(1)
	{
		
		
		/****************************************
		��¼������ȡ������ע�Ϳ��Բ����Ƿ���¼�ɹ���
		�˴�Ϊ�ڶ���ע��
		****************************************/
		
//		lv_task_handler();
//		
//		if(msTicks - weatherLastMsTicks > 1000)
//		{
//			weatherLastMsTicks = msTicks;
//			updateDeskopWeatherPattern(i++);
//			if(i == 39)	i = 0;
//		}
//		
//		if(msTicks - danceLastMsTicks > 50)
//		{
//			danceLastMsTicks = msTicks;
//			updateDeskopDancePattern(j++);
//			if(j==198)	j = 0;
//		}
	
	/****************************************
	****************************************/	
		
	}
}
