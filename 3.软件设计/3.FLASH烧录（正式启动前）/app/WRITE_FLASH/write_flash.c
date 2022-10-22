#include "write_flash.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "flash.h"
#include "usart.h"
u8 cityNum = 3;	//"深圳","湛江","广州","赣州","南昌","北京","上海"分别代表0~6
char wifiName[] = "nihao";
char wifiPassword[] = "nihao123";
/*
将天气图像分为5个part，共39张，每个part写8张，最后一个part写7张
每次烧录代码，只保留一个宏定义。共需进行5次烧录才能完成天气图像存储
天气图像存储于0block~4block（每张2sector,每个block存8张,共39张,需5个block）
*/
//#define WEATHER_WRITE_PART1
//#define WEATHER_WRITE_PART2
//#define WEATHER_WRITE_PART3
//#define WEATHER_WRITE_PART4
//#define WEATHER_WRITE_PART5




/*
将桌面gif分为14个part，共198张。每个part写15张，最后一个part写3张
同理，只保留一个宏定义。共需进行14次烧录
桌面gif存储于5block~44block（每张3sector,每个block存5张,共198张,需20个block）
*/
//#define DANCE_WRITE_PART1
//#define DANCE_WRITE_PART2
//#define DANCE_WRITE_PART3
//#define DANCE_WRITE_PART4
//#define DANCE_WRITE_PART5
//#define DANCE_WRITE_PART6
//#define DANCE_WRITE_PART7
//#define DANCE_WRITE_PART8
//#define DANCE_WRITE_PART9
//#define DANCE_WRITE_PART10
//#define DANCE_WRITE_PART11
//#define DANCE_WRITE_PART12
//#define DANCE_WRITE_PART13
//#define DANCE_WRITE_PART14




/*
第45个block存放城市、wifi账号、wifi密码
其中：
第0个sector的前三个字节：城市序号、账号长度、密码长度
第1个sector存放wifi账号
第2个sector存放wifi密码
*/
//#define CITY_WIFI_PART






/*
第46~125个block存放picture功能的cat裸眼3D图片
共80个block，40帧图像，每帧占用两个block
*/

//#define CAT_PATTERN_PART1
//#define CAT_PATTERN_PART2
//#define CAT_PATTERN_PART3
//#define CAT_PATTERN_PART4
//#define CAT_PATTERN_PART5
//#define CAT_PATTERN_PART6
//#define CAT_PATTERN_PART7
//#define CAT_PATTERN_PART8
//#define CAT_PATTERN_PART9
//#define CAT_PATTERN_PART10

void writeFlashWeatherPattern(void)
{
#if (defined WEATHER_WRITE_PART1)||(defined WEATHER_WRITE_PART2)||(defined WEATHER_WRITE_PART3)||(defined WEATHER_WRITE_PART4)||(defined WEATHER_WRITE_PART5)	
	u8 block,sector;
#endif
#ifdef WEATHER_WRITE_PART1
	block = 0;	sector = 0;
	const lv_img_dsc_t* weatherPatternPointArr[8]={
	&screen_weather_pattern0,&screen_weather_pattern1,&screen_weather_pattern2,&screen_weather_pattern3,
		&screen_weather_pattern4,&screen_weather_pattern5,&screen_weather_pattern6,&screen_weather_pattern7,
	};
#endif

#ifdef WEATHER_WRITE_PART2
	block = 1;	sector = 0;
	const lv_img_dsc_t* weatherPatternPointArr[8]={
	&screen_weather_pattern8,&screen_weather_pattern9,&screen_weather_pattern10,&screen_weather_pattern11,
	&screen_weather_pattern12,&screen_weather_pattern13,&screen_weather_pattern14,&screen_weather_pattern15
	};
#endif	
	
#ifdef WEATHER_WRITE_PART3
	block = 2;	sector = 0;
	const lv_img_dsc_t* weatherPatternPointArr[8]={
	&screen_weather_pattern16,&screen_weather_pattern17,&screen_weather_pattern18,&screen_weather_pattern19,
	&screen_weather_pattern20,&screen_weather_pattern21,&screen_weather_pattern22,&screen_weather_pattern23
	};
#endif	

#ifdef WEATHER_WRITE_PART4
	block = 3;	sector = 0;
	const lv_img_dsc_t* weatherPatternPointArr[8]={
	&screen_weather_pattern24,&screen_weather_pattern25,&screen_weather_pattern26,&screen_weather_pattern27,
	&screen_weather_pattern28,&screen_weather_pattern29,&screen_weather_pattern30,&screen_weather_pattern31
	};
#endif		
	
#ifdef WEATHER_WRITE_PART5
	block = 4;	sector = 0;
	const lv_img_dsc_t* weatherPatternPointArr[7]={
	&screen_weather_pattern32,&screen_weather_pattern33,&screen_weather_pattern34,&screen_weather_pattern35,
	&screen_weather_pattern36,&screen_weather_pattern37,&screen_weather_pattern38
	};
#endif			

#if (defined WEATHER_WRITE_PART1)||(defined WEATHER_WRITE_PART2)||(defined WEATHER_WRITE_PART3)||(defined WEATHER_WRITE_PART4)||(defined WEATHER_WRITE_PART5)	
	u8 arrLen;
	if(block == 4)	arrLen = 7;
	else	arrLen = 8;
	for(u8 i = 0; i < arrLen; i++)
	{
		FLASH_WriteData(block,sector,weatherPatternPointArr[i]->data,6912);
		sector+=2;
	}	
#endif	
	
}	

//桌面gif存储于5block~44block（每张3sector,每个block存5张,共198张,需20个block）
void writeFlashDancePattern(void)
{
#ifdef DANCE_WRITE_PART1
	u8 block = 5,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_00,&screen_gif_patterndance_01,&screen_gif_patterndance_02,&screen_gif_patterndance_03,&screen_gif_patterndance_04
	,&screen_gif_patterndance_05,&screen_gif_patterndance_06,&screen_gif_patterndance_07,&screen_gif_patterndance_08,&screen_gif_patterndance_09
	,&screen_gif_patterndance_10,&screen_gif_patterndance_11,&screen_gif_patterndance_12,&screen_gif_patterndance_13,&screen_gif_patterndance_14	
	};	
#endif

#ifdef DANCE_WRITE_PART2
	u8 block = 8,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_15,&screen_gif_patterndance_16,&screen_gif_patterndance_17,&screen_gif_patterndance_18,&screen_gif_patterndance_19
	,&screen_gif_patterndance_20,&screen_gif_patterndance_21,&screen_gif_patterndance_22,&screen_gif_patterndance_23,&screen_gif_patterndance_24
	,&screen_gif_patterndance_25,&screen_gif_patterndance_26,&screen_gif_patterndance_27,&screen_gif_patterndance_28,&screen_gif_patterndance_29	
	};	
#endif

#ifdef DANCE_WRITE_PART3
	u8 block = 11,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_30,&screen_gif_patterndance_31,&screen_gif_patterndance_32,&screen_gif_patterndance_33,&screen_gif_patterndance_34
	,&screen_gif_patterndance_35,&screen_gif_patterndance_36,&screen_gif_patterndance_37,&screen_gif_patterndance_38,&screen_gif_patterndance_39
	,&screen_gif_patterndance_40,&screen_gif_patterndance_41,&screen_gif_patterndance_42,&screen_gif_patterndance_43,&screen_gif_patterndance_44	
	};
#endif	
	
#ifdef DANCE_WRITE_PART4
	u8 block = 14,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_45,&screen_gif_patterndance_46,&screen_gif_patterndance_47,&screen_gif_patterndance_48,&screen_gif_patterndance_49
	,&screen_gif_patterndance_50,&screen_gif_patterndance_51,&screen_gif_patterndance_52,&screen_gif_patterndance_53,&screen_gif_patterndance_54
	,&screen_gif_patterndance_55,&screen_gif_patterndance_56,&screen_gif_patterndance_57,&screen_gif_patterndance_58,&screen_gif_patterndance_59	
	};
#endif	
	
#ifdef DANCE_WRITE_PART5
	u8 block = 17,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_60,&screen_gif_patterndance_61,&screen_gif_patterndance_62,&screen_gif_patterndance_63,&screen_gif_patterndance_64
	,&screen_gif_patterndance_65,&screen_gif_patterndance_66,&screen_gif_patterndance_67,&screen_gif_patterndance_68,&screen_gif_patterndance_69
	,&screen_gif_patterndance_70,&screen_gif_patterndance_71,&screen_gif_patterndance_72,&screen_gif_patterndance_73,&screen_gif_patterndance_74	
	};	
#endif
	
#ifdef DANCE_WRITE_PART6
	u8 block = 20,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_75,&screen_gif_patterndance_76,&screen_gif_patterndance_77,&screen_gif_patterndance_78,&screen_gif_patterndance_79
	,&screen_gif_patterndance_80,&screen_gif_patterndance_81,&screen_gif_patterndance_82,&screen_gif_patterndance_83,&screen_gif_patterndance_84
	,&screen_gif_patterndance_85,&screen_gif_patterndance_86,&screen_gif_patterndance_87,&screen_gif_patterndance_88,&screen_gif_patterndance_89	
	};
#endif

#ifdef DANCE_WRITE_PART7
	u8 block = 23,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_90,&screen_gif_patterndance_91,&screen_gif_patterndance_92,&screen_gif_patterndance_93,&screen_gif_patterndance_94
	,&screen_gif_patterndance_95,&screen_gif_patterndance_96,&screen_gif_patterndance_97,&screen_gif_patterndance_98,&screen_gif_patterndance_99
	,&screen_gif_patterndance_100,&screen_gif_patterndance_101,&screen_gif_patterndance_102,&screen_gif_patterndance_103,&screen_gif_patterndance_104	
	};
#endif
	
#ifdef DANCE_WRITE_PART8
	u8 block = 26,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_105,&screen_gif_patterndance_106,&screen_gif_patterndance_107,&screen_gif_patterndance_108,&screen_gif_patterndance_109
	,&screen_gif_patterndance_110,&screen_gif_patterndance_111,&screen_gif_patterndance_112,&screen_gif_patterndance_113,&screen_gif_patterndance_114
	,&screen_gif_patterndance_115,&screen_gif_patterndance_116,&screen_gif_patterndance_117,&screen_gif_patterndance_118,&screen_gif_patterndance_119	
	};	
#endif
	
#ifdef DANCE_WRITE_PART9
	u8 block = 29,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_120,&screen_gif_patterndance_121,&screen_gif_patterndance_122,&screen_gif_patterndance_123,&screen_gif_patterndance_124
	,&screen_gif_patterndance_125,&screen_gif_patterndance_126,&screen_gif_patterndance_127,&screen_gif_patterndance_128,&screen_gif_patterndance_129
	,&screen_gif_patterndance_130,&screen_gif_patterndance_131,&screen_gif_patterndance_132,&screen_gif_patterndance_134,&screen_gif_patterndance_135	
	};
#endif	

#ifdef DANCE_WRITE_PART10
	u8 block = 32,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_135,&screen_gif_patterndance_136,&screen_gif_patterndance_137,&screen_gif_patterndance_138,&screen_gif_patterndance_139
	,&screen_gif_patterndance_140,&screen_gif_patterndance_141,&screen_gif_patterndance_142,&screen_gif_patterndance_143,&screen_gif_patterndance_144
	,&screen_gif_patterndance_145,&screen_gif_patterndance_146,&screen_gif_patterndance_147,&screen_gif_patterndance_148,&screen_gif_patterndance_149	
	};	
#endif	
	
#ifdef DANCE_WRITE_PART11
	u8 block = 35,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_150,&screen_gif_patterndance_151,&screen_gif_patterndance_152,&screen_gif_patterndance_153,&screen_gif_patterndance_154
	,&screen_gif_patterndance_155,&screen_gif_patterndance_156,&screen_gif_patterndance_157,&screen_gif_patterndance_158,&screen_gif_patterndance_159
	,&screen_gif_patterndance_160,&screen_gif_patterndance_161,&screen_gif_patterndance_162,&screen_gif_patterndance_163,&screen_gif_patterndance_164	
	};
#endif

#ifdef DANCE_WRITE_PART12
	u8 block = 38,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_165,&screen_gif_patterndance_166,&screen_gif_patterndance_167,&screen_gif_patterndance_168,&screen_gif_patterndance_169
	,&screen_gif_patterndance_170,&screen_gif_patterndance_171,&screen_gif_patterndance_172,&screen_gif_patterndance_173,&screen_gif_patterndance_174
	,&screen_gif_patterndance_175,&screen_gif_patterndance_176,&screen_gif_patterndance_177,&screen_gif_patterndance_178,&screen_gif_patterndance_179	
	};
#endif	
	
#ifdef DANCE_WRITE_PART13
	u8 block = 41,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[15] = {
	&screen_gif_patterndance_180,&screen_gif_patterndance_181,&screen_gif_patterndance_182,&screen_gif_patterndance_183,&screen_gif_patterndance_184
	,&screen_gif_patterndance_185,&screen_gif_patterndance_186,&screen_gif_patterndance_187,&screen_gif_patterndance_188,&screen_gif_patterndance_189
	,&screen_gif_patterndance_190,&screen_gif_patterndance_191,&screen_gif_patterndance_192,&screen_gif_patterndance_193,&screen_gif_patterndance_194	
	};
#endif	

#ifdef DANCE_WRITE_PART14
	u8 block = 44,sector = 0;
	const lv_img_dsc_t* dancePatternPointArr[3] = {
	&screen_gif_patterndance_195,&screen_gif_patterndance_196,&screen_gif_patterndance_197
	};
#endif	
	
	
#if (defined DANCE_WRITE_PART1)||(defined DANCE_WRITE_PART2)||(defined DANCE_WRITE_PART3)||(defined DANCE_WRITE_PART4)||(defined DANCE_WRITE_PART5)||(defined DANCE_WRITE_PART6)||(defined DANCE_WRITE_PART7)||(defined DANCE_WRITE_PART8)||(defined DANCE_WRITE_PART9)||(defined DANCE_WRITE_PART10)||(defined DANCE_WRITE_PART11)||(defined DANCE_WRITE_PART12)||(defined DANCE_WRITE_PART13)		
	for(u8 i = 0; i < 15; i++)
	{
		FLASH_WriteData(block,sector,dancePatternPointArr[i]->data,10800);
		sector+=3;
		if(sector == 15)
		{
			block++;
			sector = 0;
		}
	}
#endif
	
#if (defined DANCE_WRITE_PART14)	
	for(u8 i = 0; i < 3; i++)
	{
		FLASH_WriteData(block,sector,dancePatternPointArr[i]->data,10800);
		sector+=3;
		if(sector == 15)
		{
			block++;
			sector = 0;
		}
	}
#endif
	
}

void writeFlashCityWifi(void)
{
#ifdef CITY_WIFI_PART
	u8 wifiNameLen = strlen(wifiName);
	u8 wifiPasswordLen = strlen(wifiPassword);
	
	u8 cityNumArr[3] = {cityNum,wifiNameLen,wifiPasswordLen};
	FLASH_WriteData(45,0,cityNumArr,3);
	FLASH_WriteData(45,1,(u8*)wifiName,wifiNameLen);
	FLASH_WriteData(45,2,(u8*)wifiPassword,wifiPasswordLen);
#endif
}

/*
第46~125个block存放picture功能的cat裸眼3D图片
共80个block，40帧图像，每帧占用两个block
*/

void writeFlash3DPattern(void)
{
#ifdef CAT_PATTERN_PART1
	extern const u8 catFrame1[115200],catFrame2[115200],catFrame3[115200],catFrame4[115200];
	u8 block = 46,sector = 0;
	const u8* arrP[4] = {catFrame1,catFrame2,catFrame3,catFrame4};
#endif
	
#ifdef CAT_PATTERN_PART2
	extern const u8 catFrame5[115200],catFrame6[115200],catFrame7[115200],catFrame8[115200];
	u8 block = 54,sector = 0;
	const u8* arrP[4] = {catFrame5,catFrame6,catFrame7,catFrame8};
#endif	
	
#ifdef CAT_PATTERN_PART3
	extern const u8 catFrame9[115200],catFrame10[115200],catFrame11[115200],catFrame12[115200];
	u8 block = 62,sector = 0;
	const u8* arrP[4] = {catFrame9,catFrame10,catFrame11,catFrame12};
#endif	
	
#ifdef CAT_PATTERN_PART4
	extern const u8 catFrame13[115200],catFrame14[115200],catFrame15[115200],catFrame16[115200];
	u8 block = 70,sector = 0;
	const u8* arrP[4] = {catFrame13,catFrame14,catFrame15,catFrame16};
#endif
	
#ifdef CAT_PATTERN_PART5
	extern const u8 catFrame17[115200],catFrame18[115200],catFrame19[115200],catFrame20[115200];
	u8 block = 78,sector = 0;
	const u8* arrP[4] = {catFrame17,catFrame18,catFrame19,catFrame20};
#endif	
	
#ifdef CAT_PATTERN_PART6
	extern const u8 catFrame21[115200],catFrame22[115200],catFrame23[115200],catFrame24[115200];
	u8 block = 86,sector = 0;
	const u8* arrP[4] = {catFrame21,catFrame22,catFrame23,catFrame24};
#endif	
	
#ifdef CAT_PATTERN_PART7
	extern const u8 catFrame25[115200],catFrame26[115200],catFrame27[115200],catFrame28[115200];
	u8 block = 94,sector = 0;
	const u8* arrP[4] = {catFrame25,catFrame26,catFrame27,catFrame28};
#endif		
	
#ifdef CAT_PATTERN_PART8
	extern const u8 catFrame29[115200],catFrame30[115200],catFrame31[115200],catFrame32[115200];
	u8 block = 102,sector = 0;
	const u8* arrP[4] = {catFrame29,catFrame30,catFrame31,catFrame32};
#endif		

#ifdef CAT_PATTERN_PART9
	extern const u8 catFrame33[115200],catFrame34[115200],catFrame35[115200],catFrame36[115200];
	u8 block = 110,sector = 0;
	const u8* arrP[4] = {catFrame33,catFrame34,catFrame35,catFrame36};
#endif		
	
#ifdef CAT_PATTERN_PART10
	extern const u8 catFrame37[115200],catFrame38[115200],catFrame39[115200],catFrame40[115200];
	u8 block = 118,sector = 0;
	const u8* arrP[4] = {catFrame37,catFrame38,catFrame39,catFrame40};
#endif	
	
#if (defined CAT_PATTERN_PART1)||(defined CAT_PATTERN_PART2)||(defined CAT_PATTERN_PART3)||(defined CAT_PATTERN_PART4)||(defined CAT_PATTERN_PART5)||(defined CAT_PATTERN_PART6)||(defined CAT_PATTERN_PART7)||(defined CAT_PATTERN_PART8)||(defined CAT_PATTERN_PART9)||(defined CAT_PATTERN_PART10)
	for(u8 i = 0; i < 4; i++)
	{
		FLASH_WriteData(block,sector,arrP[i],57600);	//每个block存半张
		block++;
		FLASH_WriteData(block,sector,arrP[i]+57600,57600);
		block++;
	}
#endif

}








