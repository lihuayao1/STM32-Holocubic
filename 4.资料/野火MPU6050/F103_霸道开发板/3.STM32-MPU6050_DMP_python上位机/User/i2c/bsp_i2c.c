/**
  ******************************************************************************
  * @file    bsp_i2c_ee.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   i2c mpu6050应用函数bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 


#include "./i2c/bsp_i2c.h"
#include "./systick/bsp_SysTick.h"



#define Delay mdelay

/* STM32 I2C 快速模式 */
#define I2C_Speed              400000  //*

/* 这个地址只要与STM32外挂的I2C器件地址不一样即可 */
#define I2Cx_OWN_ADDRESS7      0X0A   


static __IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;    



/********************************* Prototypes *********************************/
unsigned long ST_Hard_Sensors_I2C_WriteRegister(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, const unsigned char *RegisterValue);
unsigned long ST_Hard_Sensors_I2C_ReadRegister(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, unsigned char *RegisterValue);
/*******************************  Function ************************************/

//若定义了这个宏，使用硬件iic，否则使用软件iic。这个宏在bsp_i2c.h文件定义
//使用硬件IIC时不能与液晶屏共用，因为FSMC的NADV与IIC1的SDA 是同一个引脚，互相影响了

#ifdef HARD_IIC

#define ST_Sensors_I2C_WriteRegister  ST_Hard_Sensors_I2C_WriteRegister
#define ST_Sensors_I2C_ReadRegister ST_Hard_Sensors_I2C_ReadRegister

static uint8_t I2C_TIMEOUT_UserCallback(uint8_t errorCode);


#else
//
#define Soft_I2C_SDA_STATE   	GPIO_ReadInputDataBit(Soft_I2C_PORT, Soft_I2C_SDA)
#define Soft_I2C_DELAY 				Soft_I2C_Delay(100000)
#define Soft_I2C_NOP					Soft_I2C_Delay(10) 
//
#define Soft_I2C_READY		0x00
#define Soft_I2C_BUS_BUSY	0x01	
#define Soft_I2C_BUS_ERROR	0x02
//
#define Soft_I2C_NACK	  0x00 
#define Soft_I2C_ACK		0x01


//
static void Soft_I2C_Configuration(void);
static void Soft_I2C_Delay(uint32_t dly);
static uint8_t Soft_I2C_START(void);
static void Soft_I2C_STOP(void);
static void Soft_I2C_SendACK(void);
static void Soft_I2C_SendNACK(void);
static uint8_t Soft_I2C_SendByte(uint8_t anbt_i2c_data);
static uint8_t Soft_I2C_ReceiveByte_WithACK(void);
static uint8_t Soft_I2C_ReceiveByte(void);
static uint8_t Soft_DMP_I2C_Write(uint8_t soft_dev_addr, uint8_t soft_reg_addr, uint8_t soft_i2c_len,unsigned char *soft_i2c_data_buf);
static uint8_t Soft_DMP_I2C_Read(uint8_t soft_dev_addr, uint8_t soft_reg_addr, uint8_t soft_i2c_len,unsigned char *soft_i2c_data_buf);


#define ST_Sensors_I2C_WriteRegister  Soft_DMP_I2C_Write
#define ST_Sensors_I2C_ReadRegister Soft_DMP_I2C_Read

#endif

#ifdef HARD_IIC
/**
  * @brief  I2C1 I/O配置
  * @param  无
  * @retval 无
  */
static void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* 使能与 I2C1 有关的时钟 */
	SENSORS_I2C_APBxClock_FUN ( SENSORS_I2C_CLK, ENABLE );
	SENSORS_I2C_GPIO_APBxClock_FUN ( SENSORS_I2C_GPIO_CLK, ENABLE );
	
    
  /* PB6-I2C1_SCL、PB7-I2C1_SDA*/
  GPIO_InitStructure.GPIO_Pin = SENSORS_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // 开漏输出
  GPIO_Init(SENSORS_I2C_SCL_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = SENSORS_I2C_SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // 开漏输出
  GPIO_Init(SENSORS_I2C_SDA_PORT, &GPIO_InitStructure);	
	
	
}


/**
  * @brief  I2C 工作模式配置
  * @param  无
  * @retval 无
  */
static void I2C_Mode_Configu(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 

  /* I2C 配置 */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	
	/* 高电平数据稳定，低电平数据变化 SCL 时钟线的占空比 */
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	
  I2C_InitStructure.I2C_OwnAddress1 =I2Cx_OWN_ADDRESS7; 
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
	
	/* I2C的寻址模式 */
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	/* 通信速率 */
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
	/* I2C1 初始化 */
  I2C_Init(SENSORS_I2Cx, &I2C_InitStructure);
  
	/* 使能 I2C1 */
  I2C_Cmd(SENSORS_I2Cx, ENABLE);   
}



/**
  * @brief  向IIC设备的寄存器连续写入数据
  * @param  Address: IIC设备地址
  * @param  RegisterAddr: 寄存器地址
  * @param  RegisterLen: 要写入数据的长度
  * @param  RegisterValue: 要指向写入数据的指针
  * @retval 0正常，非0异常
  */
unsigned long ST_Hard_Sensors_I2C_WriteRegister(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, const unsigned char *RegisterValue)
{
	 uint32_t i=0;
	
	 /* Send STRAT condition */
	  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);

		I2CTimeout = I2CT_FLAG_TIMEOUT;


	  /* Test on EV5 and clear it */
	  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
	  {
	    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
	  }

	  /* Send slave address for write */
	  I2C_Send7bitAddress(SENSORS_I2Cx, (Address<<1), I2C_Direction_Transmitter);

		I2CTimeout = I2CT_FLAG_TIMEOUT;
	  /* Test on EV6 and clear it */
	  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		{
	    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(1);
	  }

	  /* Send the slave's internal address to write to */
	  I2C_SendData(SENSORS_I2Cx, RegisterAddr);

		I2CTimeout = I2CT_FLAG_TIMEOUT;
	  /* Test on EV8 and clear it */
	  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		{
	    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(2);
	  }

	  /* Send the byte to be written */
	  for( i=0; i<(RegisterLen); i++)
	   {
		  	  I2CTimeout = I2CT_FLAG_TIMEOUT;
		  	  /* Test on EV8 and clear it */
		  	  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		  		{
		  	    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
		  	  }

	     /* Prepare the register value to be sent */
	     I2C_SendData(SENSORS_I2Cx, RegisterValue[i]);
	   }

		I2CTimeout = I2CT_FLAG_TIMEOUT;

	  /* Test on EV8 and clear it */
	  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		{
	    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(4);
	  }

	  /* Send STOP condition */
	  I2C_GenerateSTOP(SENSORS_I2Cx, ENABLE);

		return 0; //正常返回0
}


/**
  * @brief  向IIC设备的寄存器连续读出数据
  * @param  Address: IIC设备地址
  * @param  RegisterAddr: 寄存器地址
  * @param  RegisterLen: 要读取的数据长度
  * @param  RegisterValue: 指向存储读出数据的指针
  * @retval 0正常，非0异常
  */
unsigned long ST_Hard_Sensors_I2C_ReadRegister(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, unsigned char *RegisterValue)
{
	 I2CTimeout = I2CT_LONG_TIMEOUT;

	  while(I2C_GetFlagStatus(SENSORS_I2Cx, I2C_FLAG_BUSY)) // Added by Najoua 27/08/2008
	  {
	    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(5);
	   }

	  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);

		I2CTimeout = I2CT_FLAG_TIMEOUT;

	  /* Test on EV5 and clear it */
	  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
		{
	    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(6);
	   }

	  /* Send slave address for write */
	  I2C_Send7bitAddress(SENSORS_I2Cx, (Address<<1), I2C_Direction_Transmitter);

		I2CTimeout = I2CT_FLAG_TIMEOUT;

	  /* Test on EV6 and clear it */
	  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		{
	    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(7);
	   }

	  /* Clear EV6 by setting again the PE bit */
	  I2C_Cmd(SENSORS_I2Cx, ENABLE);

	  /* Send the slave's internal address to write to */
	  I2C_SendData(SENSORS_I2Cx, RegisterAddr);

		I2CTimeout = I2CT_FLAG_TIMEOUT;

	  /* Test on EV8 and clear it */
	  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		{
	    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(8);
	   }

	  /* Send STRAT condition a second time */
	  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);

		I2CTimeout = I2CT_FLAG_TIMEOUT;
	  /* Test on EV5 and clear it */
	  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
		{
	    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(9);
	   }

	  /* Send slave address for read */
	  I2C_Send7bitAddress(SENSORS_I2Cx, (Address<<1), I2C_Direction_Receiver);

		I2CTimeout = I2CT_FLAG_TIMEOUT;

	  /* Test on EV6 and clear it */
	  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
		{
	    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(10);
	   }

	  /* While there is data to be read */
	  while(RegisterLen)
	  {
	    if(RegisterLen == 1)
	    {
	      /* Disable Acknowledgement */
	      I2C_AcknowledgeConfig(SENSORS_I2Cx, DISABLE);

	      /* Send STOP Condition */
	      I2C_GenerateSTOP(SENSORS_I2Cx, ENABLE);
	    }

			I2CTimeout = I2CT_LONG_TIMEOUT;
			while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
			{
				if((I2CTimeout--) == 0) 
				{

						return I2C_TIMEOUT_UserCallback(10);
				}
			 }
			
	    {
	      /* Read a byte from the slave */
	      *RegisterValue = I2C_ReceiveData(SENSORS_I2Cx);

	      /* Point to the next location where the byte read will be saved */
	      RegisterValue++;

	      /* Decrement the read bytes counter */
	      RegisterLen--;
	    }

	  }

	  /* Enable Acknowledgement to be ready for another reception */
	  I2C_AcknowledgeConfig(SENSORS_I2Cx, ENABLE);

		return 0; //正常，返回0
}






/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
static  uint8_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
	/*重置IIC*/
  I2C_GenerateSTOP(SENSORS_I2Cx, ENABLE);
  I2C_SoftwareResetCmd(SENSORS_I2Cx, ENABLE);
  I2C_SoftwareResetCmd(SENSORS_I2Cx, DISABLE);
	
	I2C_Bus_Init();
	
  /* Block communication and all processes */
  MPU_ERROR("I2C Timeout error! error code = %d",errorCode);
  
  return 1;
}

#endif //endof #ifdef HARD_IIC



/**
  * @brief  I2C 外设初始化
  * @param  无
  * @retval 无
  */
void I2C_Bus_Init(void)
{	
	
	Set_I2C_Retry(5);
	
	#ifdef HARD_IIC
	MPU_DEBUG("hard iic");
	
  I2C_GPIO_Config(); 
 
  I2C_Mode_Configu();
	
	#else
	
  MPU_DEBUG("soft iic");
	Soft_I2C_Configuration();
	
	#endif

}






/**
  * @brief  向IIC设备的寄存器连续写入数据，带超时重试设置，供mpu接口调用
  * @param  Address: IIC设备地址
  * @param  RegisterAddr: 寄存器地址
  * @param  RegisterLen: 要写入数据的长度
  * @param  RegisterValue: 要指向写入数据的指针
  * @retval 0正常，非0异常
  */
int Sensors_I2C_WriteRegister(unsigned char slave_addr,
                                        unsigned char reg_addr,
                                        unsigned short len,
                                        const unsigned char *data_ptr)
{
  char retries=0;
  int ret = 0;
  unsigned short retry_in_mlsec = Get_I2C_Retry();

tryWriteAgain:
  ret = 0;
  ret = ST_Sensors_I2C_WriteRegister( slave_addr, reg_addr, len, ( unsigned char *)data_ptr);

  if(ret && retry_in_mlsec)
  {
    if( retries++ > 4 )
        return ret;

    mdelay(retry_in_mlsec);
    goto tryWriteAgain;
  }
  return ret;
}


/**
  * @brief  向IIC设备的寄存器连续读出数据,带超时重试设置，供mpu接口调用
  * @param  Address: IIC设备地址
  * @param  RegisterAddr: 寄存器地址
  * @param  RegisterLen: 要读取的数据长度
  * @param  RegisterValue: 指向存储读出数据的指针
  * @retval 0正常，非0异常
  */
int Sensors_I2C_ReadRegister(unsigned char slave_addr,
                                       unsigned char reg_addr,
                                       unsigned short len,
                                       unsigned char *data_ptr)
{
  char retries=0;
  int ret = 0;
  unsigned short retry_in_mlsec = Get_I2C_Retry();

tryReadAgain:
  ret = 0;
  ret = ST_Sensors_I2C_ReadRegister( slave_addr, reg_addr, len, ( unsigned char *)data_ptr);

  if(ret && retry_in_mlsec)
  {
    if( retries++ > 4 )
        return ret;

    mdelay(retry_in_mlsec);
    goto tryReadAgain;
  }
  return ret;
}


static unsigned short RETRY_IN_MLSEC  = 55;

/**
  * @brief  设置iic重试时间
  * @param  ml_sec：重试的时间，单位毫秒
  * @retval 重试的时间，单位毫秒
  */
void Set_I2C_Retry(unsigned short ml_sec)
{
  RETRY_IN_MLSEC = ml_sec;
}

/**
  * @brief  获取设置的iic重试时间
  * @param  none
  * @retval none
  */
unsigned short Get_I2C_Retry(void)
{
  return RETRY_IN_MLSEC;
}


/************************软件IIC驱动函数****************************************/

#ifndef HARD_IIC

static void Soft_I2C_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	//
	//
  GPIO_InitStructure.GPIO_Pin = Soft_I2C_SCL | Soft_I2C_SDA;					//配置使用的I2C口
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;   //设置I2C口最大允许输出速度
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	  //设置I2C为开漏输出
  GPIO_Init(Soft_I2C_PORT, &GPIO_InitStructure); 
	//
	//
	Soft_I2C_SCL_1; 
	Soft_I2C_SDA_1;
	Soft_I2C_DELAY; 
}

static void Soft_I2C_Delay(uint32_t dly) 
{
	while(--dly);	//dly=100: 8.75us; dly=100: 85.58 us (SYSCLK=72MHz)
}

static uint8_t Soft_I2C_START(void)
{ 
	Soft_I2C_SDA_1; 
 	Soft_I2C_NOP;
  // 
 	Soft_I2C_SCL_1; 
 	Soft_I2C_NOP;    
	//
 	if(!Soft_I2C_SDA_STATE) return Soft_I2C_BUS_BUSY;
	//
 	Soft_I2C_SDA_0;
 	Soft_I2C_NOP;
  //
 	Soft_I2C_SCL_0;  
 	Soft_I2C_NOP; 
	//
 	if(Soft_I2C_SDA_STATE) return Soft_I2C_BUS_ERROR;
	//
 	return Soft_I2C_READY;
}

static void Soft_I2C_STOP(void)
{
 	Soft_I2C_SDA_0; 
 	Soft_I2C_NOP;
  // 
 	Soft_I2C_SCL_1; 
 	Soft_I2C_NOP;    
	//
 	Soft_I2C_SDA_1;
 	Soft_I2C_NOP;
}

static void Soft_I2C_SendACK(void)
{
 	Soft_I2C_SDA_0;
 	Soft_I2C_NOP;
 	Soft_I2C_SCL_1;
 	Soft_I2C_NOP;
 	Soft_I2C_SCL_0; 
 	Soft_I2C_NOP;  
}

static void Soft_I2C_SendNACK(void)
{
	Soft_I2C_SDA_1;
	Soft_I2C_NOP;
	Soft_I2C_SCL_1;
	Soft_I2C_NOP;
	Soft_I2C_SCL_0; 
	Soft_I2C_NOP;  
}




/**
  * @brief  等待应答信号到来
  * @retval 返回值：1，接收应答失败
	*									0，接收应答成功
  */
uint8_t Soft_I2C_Wait_Ack(void)
{
	uint8_t ucErrTime=0;

	Soft_I2C_SDA_1;
	Soft_I2C_NOP;	   
	Soft_I2C_SCL_1;
	Soft_I2C_NOP;	 
	
	while(Soft_I2C_SDA_STATE)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			Soft_I2C_STOP();
			return Soft_I2C_BUS_ERROR;
		}
	}
	Soft_I2C_SCL_0;//时钟输出0 	   
	return 0;  
} 

static uint8_t Soft_I2C_SendByte(uint8_t soft_i2c_data)
{
 	uint8_t i;
 	
	Soft_I2C_SCL_0;
 	for(i=0;i<8;i++)
 	{  
  		if(soft_i2c_data&0x80) Soft_I2C_SDA_1;
   		else Soft_I2C_SDA_0;
			//
  		soft_i2c_data<<=1;
  		Soft_I2C_NOP;
			//
  		Soft_I2C_SCL_1;
  		Soft_I2C_NOP;
  		Soft_I2C_SCL_0;
  		Soft_I2C_NOP; 
 	}
	//
// 	Soft_I2C_SDA_1; 
// 	Soft_I2C_NOP;
// 	Soft_I2C_SCL_1;
// 	Soft_I2C_NOP;   
// 	if(Soft_I2C_SDA_STATE)
// 	{
//  		Soft_I2C_SCL_0;
//  		return Soft_I2C_NACK;
// 	}
// 	else
// 	{
//  		Soft_I2C_SCL_0;
//  		return Soft_I2C_ACK;  
// 	}  
	return Soft_I2C_Wait_Ack();  
}

static uint8_t Soft_I2C_ReceiveByte(void)
{
	uint8_t i,soft_i2c_data;
	//
 	Soft_I2C_SDA_1;
 	Soft_I2C_SCL_0; 
 	soft_i2c_data=0;
	//
 	for(i=0;i<8;i++)
 	{
  		Soft_I2C_SCL_1;
  		Soft_I2C_NOP; 
  		soft_i2c_data<<=1;
			//
  		if(Soft_I2C_SDA_STATE)	soft_i2c_data|=0x01; 
  
  		Soft_I2C_SCL_0;  
  		Soft_I2C_NOP;         
 	}
	Soft_I2C_SendNACK();
 	return soft_i2c_data;
}

static uint8_t Soft_I2C_ReceiveByte_WithACK(void)
{
	uint8_t i,soft_i2c_data;
	//
 	Soft_I2C_SDA_1;
 	Soft_I2C_SCL_0; 
 	soft_i2c_data=0;
	//
 	for(i=0;i<8;i++)
 	{
  		Soft_I2C_SCL_1;
  		Soft_I2C_NOP; 
  		soft_i2c_data<<=1;
			//
  		if(Soft_I2C_SDA_STATE)	soft_i2c_data|=0x01; 
  
  		Soft_I2C_SCL_0;  
  		Soft_I2C_NOP;         
 	}
	Soft_I2C_SendACK();
 	return soft_i2c_data;
}


//static void Soft_DMP_Delay_us(uint32_t dly)
//{
//	uint8_t i;
//	while(dly--) for(i=0;i<10;i++);
//}
////
//static void Soft_DMP_Delay_ms(uint32_t dly)
//{
//	while(dly--) Soft_DMP_Delay_us(1000);
//}
//

static uint8_t Soft_DMP_I2C_Write(uint8_t soft_dev_addr, uint8_t soft_reg_addr, uint8_t soft_i2c_len,unsigned char *soft_i2c_data_buf)
{		
		uint8_t i, result=0;
		Soft_I2C_START();
		result  = Soft_I2C_SendByte(soft_dev_addr << 1 | I2C_Direction_Transmitter);	
		if(result != 0) return result;
	
		result = Soft_I2C_SendByte(soft_reg_addr);  
		if(result != 0) return result;
	
		for (i=0;i<soft_i2c_len;i++) 
		{
			result = Soft_I2C_SendByte(soft_i2c_data_buf[i]); 
			if (result != 0) return result;
		}
		Soft_I2C_STOP();
		return 0x00;
}

static uint8_t Soft_DMP_I2C_Read(uint8_t soft_dev_addr, uint8_t soft_reg_addr, uint8_t soft_i2c_len,unsigned char *soft_i2c_data_buf)
{
		uint8_t result;
	
		Soft_I2C_START();
		result  = Soft_I2C_SendByte(soft_dev_addr << 1 | I2C_Direction_Transmitter);			
		if(result != 0) return result;

		result = Soft_I2C_SendByte(soft_reg_addr); 
		if(result != 0) return result;

		Soft_I2C_START();
		result = Soft_I2C_SendByte(soft_dev_addr << 1 | I2C_Direction_Receiver);
		if(result != 0) return result;
	
		//
    while (soft_i2c_len)
		{
			if (soft_i2c_len==1) *soft_i2c_data_buf =Soft_I2C_ReceiveByte();  
      else *soft_i2c_data_buf =Soft_I2C_ReceiveByte_WithACK();
      soft_i2c_data_buf++;
      soft_i2c_len--;
    }
		Soft_I2C_STOP();
    return 0x00;
}

#endif //endof #ifndef HARD_IIC
/*********************************************END OF FILE**********************/

