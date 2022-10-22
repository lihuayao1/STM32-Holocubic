#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <windows.h>
#include <stdio.h>
#include <cstring>
#include  <stdlib.h>
using namespace std;
using namespace cv;
Mat bmpSrc;

unsigned char bmpData[240 * 240 * 2] = {0};
char bmpName[20];
char tempStr[10];
void intToString(int num, char str[])
{
	int stack[10],top = -1;
	int pos = 0;
	memset(str,0,sizeof(str));
	while (num != 0)
	{
		stack[++top] = (num % 10) + '0';
		num = num / 10;
	}

	while (top >= 0)
		str[pos++] = stack[top--];
}

char arrName[50];
char fileName[50];
FILE *fp;
int main()
{
	for (int i = 1; i <= 40; i++)
	{
		memset(fileName,0,sizeof(fileName));
		strcpy(fileName,".\\bmpData\\catPattern");
		intToString(i, tempStr);	strcat(fileName,tempStr);
		strcat(fileName,".c");
		fp = fopen(fileName, "w");
		//printf("%s\n", fileName);
		memset(bmpName, 0, sizeof(bmpName));
		strcpy(bmpName, ".\\bmp\\cat");
		intToString(i, tempStr);
		strcat(bmpName, tempStr);
		strcat(bmpName, ".bmp");

		bmpSrc = imread(bmpName);
		cvtColor(bmpSrc, bmpSrc, COLOR_BGR2RGB);

		int pos = 0, temp;
		for (int i = 0; i < bmpSrc.rows*bmpSrc.cols * 3; i++)
		{
			if (i % 3 == 0)			//R五位
				bmpData[pos] = ((bmpSrc.data[i] * 32 / 256) << 3);
			else if (i % 3 == 1)	//G六位
			{
				temp = (bmpSrc.data[i] * 64 / 256);
				bmpData[pos] |= (temp >> 3);
				pos++;
				bmpData[pos] = temp << 5;
			}
			else if (i % 3 == 2)	//B五位
			{
				temp = (bmpSrc.data[i] * 32 / 256);
				bmpData[pos] |= temp;
				pos++;
			}
		}
		fprintf(fp,"#include \"stm32f4xx.h\"\n");

		memset(arrName, 0, sizeof(arrName));
		strcpy(arrName, "const u8 catFrame"); intToString(i, tempStr);	strcat(arrName, tempStr);
		strcat(arrName, "[115200]={\n");

		fprintf(fp, "%s", arrName);
		for (int i = 1; i <= pos; i++)
		{
			if (i != pos)
				fprintf(fp, "0x%x,", bmpData[i-1]);
			else
				fprintf(fp, "0x%x};", bmpData[i-1]);

			if(i % 20 == 0)
				fprintf(fp, "\n");
		}
			
		fprintf(fp, "\n\n");
		printf("已写入%d张\n", i);
		pos = 0;
	}

	/*for (int i = 1; i <= 40; i++)
	{
		memset(bmpName,0,sizeof(bmpName));
		strcpy(bmpName,".\\bmp\\cat");
		intToString(i, tempStr);	
		strcat(bmpName,tempStr);
		strcat(bmpName,".bmp");
		
		bmpSrc = imread(bmpName);
		cvtColor(bmpSrc, bmpSrc, COLOR_BGR2RGB);

		int pos = 0,temp;
		for (int i = 0; i < bmpSrc.rows*bmpSrc.cols * 3; i++)
		{
			if (i % 3 == 0)			//R五位
				bmpData[pos] = ((bmpSrc.data[i] * 32 / 256) << 3);
			else if (i % 3 == 1)	//G六位
			{
				temp = (bmpSrc.data[i] * 64 / 256);
				bmpData[pos] |= (temp >> 3);
				pos++;
				bmpData[pos] = temp << 5;
			}
			else if (i % 3 == 2)	//B五位
			{
				temp = (bmpSrc.data[i] * 32 / 256);
				bmpData[pos] |= temp;
				pos++;
			}
		}
		memset(arrName,0,sizeof(arrName));
		
		strcpy(arrName,"const u8 catFrame"); intToString(i, tempStr);	strcat(arrName, tempStr);
		strcat(arrName,"[115200]={");
		fprintf(fp, "%s", arrName);
		for (int i = 0; i < pos; i++)
			if(i!=pos-1)
				fprintf(fp,"0x%x,",bmpData[i]);
			else
				fprintf(fp, "0x%x};", bmpData[i]);
		fprintf(fp, "\n\n\n\n");
		printf("已写入%d张\n",i);
		pos = 0;

	}
	printf("\n\n全部bmp数组已存入工程目录中的bmpData.txt\n\n");*/
	waitKey(0);
}
