#include "stm32f4xx.h"
#include <stdio.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void gyro_data_ready_cb(void);
int Sensors_I2C_WriteRegister(unsigned char slave_addr,
													unsigned char reg_addr,
													unsigned short len,
													unsigned char *data_ptr);
int Sensors_I2C_ReadRegister(unsigned char slave_addr,
													unsigned char reg_addr,
													unsigned short len,
													unsigned char *data_ptr);
void get_tick_count(unsigned long *count);	//获取ms节拍数目
void MPU6050_DMP_Init(void);
int fputcc(int ch);
void MPU6050_DMP_Task(void);