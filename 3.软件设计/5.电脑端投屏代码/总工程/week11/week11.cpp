#include "pch.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <windows.h>
#include <stdio.h>
#include <cstring>

#include <tlhelp32.h>
#include <atlimage.h>
#include <time.h>
#include  <stdlib.h>
#include <conio.h>  
#include <winnt.h>  
using namespace std;
using namespace cv;
clock_t t1, t2;
Mat bmpSrc;
void getScreen()
{
	HWND hDesktopWnd = GetDesktopWindow();
	HDC hdc = GetDC(hDesktopWnd);
	HDC mdc = CreateCompatibleDC(hdc);
	int dwScreenW = GetSystemMetrics(SM_CXSCREEN);
	int dwScreenH = GetSystemMetrics(SM_CYSCREEN);
	HBITMAP bmp = CreateCompatibleBitmap(hdc, dwScreenW, dwScreenH);
	HBITMAP holdbmp = (HBITMAP)SelectObject(mdc, bmp);
	BitBlt(mdc, 0, 0, dwScreenW, dwScreenH, hdc, 0, 0, SRCCOPY);
	
	CImage image;
	image.Attach(bmp);
	image.Save(L".\\path\\screen.bmp");
}
HANDLE m_hComm;
DWORD dwLength;
DWORD dwactlen;
void comInit()
{
	DCB myDCB;

	m_hComm = CreateFile(
		L"COM7:",
		GENERIC_READ | GENERIC_WRITE,   //允许读和写  
		0,                          //独占方式（共享模式）  
		NULL,
		OPEN_EXISTING,              //打开而不是创建（创建方式）  
		0,
		NULL
	);
	if (m_hComm == (HANDLE)-1) 
	{ 	printf("打开串口失败"); return; }
	if (!GetCommState(m_hComm, &myDCB))
	{	printf("GetCommState error"); return;	}
	myDCB.BaudRate = 460800 * 6 + 230400;
	//myDCB.BaudRate = 115200;
	myDCB.fBinary = TRUE; // 设置二进制模式，此处必须设置TRUE  
	myDCB.fParity = TRUE; // 支持奇偶校验  
	myDCB.fOutxCtsFlow = FALSE;  // No CTS output flow control  
	myDCB.fOutxDsrFlow = FALSE;  // No DSR output flow control  
	myDCB.fDtrControl = DTR_CONTROL_DISABLE; // No DTR flow control  
	myDCB.fDsrSensitivity = FALSE; // DSR sensitivity  
	myDCB.fTXContinueOnXoff = TRUE; // XOFF continues Tx  
	myDCB.fOutX = FALSE;     // No XON/XOFF out flow control  
	myDCB.fInX = FALSE;        // No XON/XOFF in flow control  
	myDCB.fErrorChar = FALSE;    // Disable error replacement  
	myDCB.fNull = FALSE;  // Disable null stripping  
	myDCB.fRtsControl = RTS_CONTROL_DISABLE;   //No RTS flow control  
	myDCB.fAbortOnError = FALSE;  // 当串口发生错误，并不终止串口读写  
	myDCB.ByteSize = 8;   // 数据位,范围:4-8  
	myDCB.Parity = NOPARITY; // 校验模式  
	myDCB.StopBits = 0;   // 1位停止位
	if (!SetCommState(m_hComm, &myDCB))
	{	printf("SetCommState error");	return;	}
	SetupComm(m_hComm, 62400,62400);
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR);
	COMMTIMEOUTS TimeOuts;
	//设定读超时
	TimeOuts.ReadIntervalTimeout = 1000;
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	TimeOuts.ReadTotalTimeoutConstant = 5000;
	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(m_hComm, &TimeOuts); //设置超时 !mportant
}


unsigned char usartSendData[130 * 240 * 2] = {0}, temp;
int pos = 0;	//用于记录串口发送数据的下标
int main()
{
	_tmkdir(L"path");
	comInit();

	while (1)
	{
		getScreen();
		bmpSrc = imread(".\\path\\screen.bmp");
		resize(bmpSrc, bmpSrc, Size(240, 130));
		imwrite("screen.bmp", bmpSrc);
		cvtColor(bmpSrc, bmpSrc, COLOR_BGR2RGB);

		for (int i = 0; i < bmpSrc.rows*bmpSrc.cols * 3; i++)
		{
			if (i % 3 == 0)			//R五位
				usartSendData[pos] = ((bmpSrc.data[i] * 32 / 256) << 3);
			else if (i % 3 == 1)	//G六位
			{
				temp = (bmpSrc.data[i] * 64 / 256);
				usartSendData[pos] |= (temp >> 3);
				pos++;
				usartSendData[pos] = temp << 5;
			}
			else if (i % 3 == 2)	//B五位
			{
				temp = (bmpSrc.data[i] * 32 / 256);
				usartSendData[pos] |= temp;
				pos++;
			}
		}
		pos = 0;
		t1 = clock();
		WriteFile(m_hComm, usartSendData, 62400, &dwactlen, NULL);
		t2 = clock();
		printf("t1 = %d t2 = %d\n",t1,t2);
		Sleep(10);
	}
	waitKey(0);
}
