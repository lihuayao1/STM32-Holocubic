#ifndef __BSP_BMP_H
#define	__BSP_BMP_H


#include "stm32f10x.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>




// �ĸ��ֽڶ���  ��1�ƴ���
#define WIDTHBYTES(bits) (((bits)+31)/32*4)		//����24λ���ɫ ÿһ�е����ؿ�ȱ�����4�ı���  ����0����

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;


//λͼ�ļ�ͷ��Ϣ�ṹ����
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������Ҫ�Ǽ��˵Ļ���������ȷ��ȡ�ļ���Ϣ��
typedef struct tagBITMAPFILEHEADER 
{   
    DWORD bfSize; 															//�ļ���С																				4
    WORD bfReserved1; 													//�����֣�������		 															2
    WORD bfReserved2; 													//�����֣�ͬ��			 															2
    DWORD bfOffBits; 														//ʵ��λͼ���ݵ�ƫ���ֽ�������ǰ�������ֳ���֮��	4
} BITMAPFILEHEADER,tagBITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize; 														//ָ���˽ṹ��ĳ��ȣ�Ϊ40		 												4
    LONG biWidth; 														//λͼ��											 												4
    LONG biHeight; 														//λͼ��											 												4
    WORD biPlanes; 														//ƽ������Ϊ1								 													2
    WORD biBitCount; 													//������ɫλ����������1��2��4��8��16��24�µĿ�����32	2
    DWORD biCompression; 											//ѹ����ʽ��������0��1��2������0��ʾ��ѹ��						4
    DWORD biSizeImage; 												//ʵ��λͼ����ռ�õ��ֽ���														4
    LONG biXPelsPerMeter; 										//X����ֱ���																					4
    LONG biYPelsPerMeter; 										//Y����ֱ���																					4
    DWORD biClrUsed; 													//ʹ�õ���ɫ�������Ϊ0�����ʾĬ��ֵ(2^��ɫλ��)			4
    DWORD biClrImportant; 										//��Ҫ��ɫ�������Ϊ0�����ʾ������ɫ������Ҫ��				4
} BITMAPINFOHEADER,tagBITMAPINFOHEADER;


typedef struct tagRGBQUAD 
{
    BYTE rgbBlue; 													//����ɫ����ɫ����
    BYTE rgbGreen; 													//����ɫ����ɫ����
    BYTE rgbRed; 														//����ɫ�ĺ�ɫ����
    BYTE rgbReserved;											 	//����ֵ
} RGBQUAD,tagRGBQUAD;


typedef struct RGB_PIXEL
{      //���ص���������
    unsigned char   rgbBlue;
    unsigned char   rgbGreen;
    unsigned char   rgbRed;
}RGB_PIXEL;


#define GETR_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )RGB565) >>11)<<3))		  			//����8λ R
#define GETG_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x7ff)) >>5)<<2)) 	//����8λ G
#define GETB_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x1f))<<3)))       	//����8λ B
#pragma diag_suppress 870 	//ʹ������֧�ֶ��ֽ��ַ�,�������invalid multibyte character sequence���� 



void                   Lcd_show_bmp        ( uint16_t x, uint16_t y, uint8_t * pic_name );
int                    Screen_shot         ( uint16_t x, uint16_t y, uint16_t Width, uint16_t Height, uint8_t * filename );



#endif /* __BSP_BMP_H */

