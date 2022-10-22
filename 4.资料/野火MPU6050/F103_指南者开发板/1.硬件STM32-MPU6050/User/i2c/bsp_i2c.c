/**
  ******************************************************************************
  * @file    bsp_i2c_ee.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   i2c mpu6050Ӧ�ú���bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� ָ���� ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "./i2c/bsp_i2c.h"
#include "./mpu6050/mpu6050.h"


/* STM32 I2C ����ģʽ */
#define I2C_Speed              400000  //*

/* �����ַֻҪ��STM32��ҵ�I2C������ַ��һ������ */
#define I2Cx_OWN_ADDRESS7      0X0A   


static __IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;    


static uint8_t I2C_TIMEOUT_UserCallback(void);

/**
  * @brief  I2C1 I/O����
  * @param  ��
  * @retval ��
  */
static void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* ʹ���� I2C1 �йص�ʱ�� */
	SENSORS_I2C_APBxClock_FUN ( SENSORS_I2C_CLK, ENABLE );
	SENSORS_I2C_GPIO_APBxClock_FUN ( SENSORS_I2C_GPIO_CLK, ENABLE );
	
    
  /* PB6-I2C1_SCL��PB7-I2C1_SDA*/
  GPIO_InitStructure.GPIO_Pin = SENSORS_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // ��©���
  GPIO_Init(SENSORS_I2C_SCL_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = SENSORS_I2C_SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // ��©���
  GPIO_Init(SENSORS_I2C_SDA_PORT, &GPIO_InitStructure);	
	
	
}


/**
  * @brief  I2C ����ģʽ����
  * @param  ��
  * @retval ��
  */
static void I2C_Mode_Configu(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 

  /* I2C ���� */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	
	/* �ߵ�ƽ�����ȶ����͵�ƽ���ݱ仯 SCL ʱ���ߵ�ռ�ձ� */
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	
  I2C_InitStructure.I2C_OwnAddress1 =I2Cx_OWN_ADDRESS7; 
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
	
	/* I2C��Ѱַģʽ */
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	/* ͨ������ */
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
	/* I2C1 ��ʼ�� */
  I2C_Init(SENSORS_I2Cx, &I2C_InitStructure);
  
	/* ʹ�� I2C1 */
  I2C_Cmd(SENSORS_I2Cx, ENABLE);   
}


/**
  * @brief  I2C �����ʼ��
  * @param  ��
  * @retval ��
  */
void I2C_Bus_Init(void)
{

  I2C_GPIO_Config(); 
 
  I2C_Mode_Configu();

}




/**
  * @brief   дһ���ֽڵ�I2C�豸��
  * @param   
  *		@arg pBuffer:������ָ��
  *		@arg WriteAddr:д��ַ 
  * @retval  ��������1���쳣����0
  */
uint8_t I2C_ByteWrite(u8 pBuffer, u8 WriteAddr)
{
  /* Send STRAT condition */
  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;


  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
  } 

  /* Send slave address for write */
  I2C_Send7bitAddress(SENSORS_I2Cx, MPU6050_SLAVE_ADDRESS, I2C_Direction_Transmitter);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) 
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
  }  
      
  /* Send the slave's internal address to write to */
  I2C_SendData(SENSORS_I2Cx, WriteAddr);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
  } 

  /* Send the byte to be written */
  I2C_SendData(SENSORS_I2Cx, pBuffer); 
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;
   
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))	
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
  } 
	
  /* Send STOP condition */
  I2C_GenerateSTOP(SENSORS_I2Cx, ENABLE);
	
	return 1; //��������1
}



/**
  * @brief   ��I2C�豸�����ȡһ������ 
  * @param   
  *		@arg pBuffer:��Ŵ�slave��ȡ�����ݵĻ�����ָ��
  *		@arg WriteAddr:�������ݵĴ��豸�ĵ�ַ
  *     @arg NumByteToWrite:Ҫ�Ӵ��豸��ȡ���ֽ���
  * @retval  ��������1���쳣����0
  */
uint8_t I2C_BufferRead(u8* pBuffer, u8 ReadAddr, u16 NumByteToRead)
{  
  I2CTimeout = I2CT_LONG_TIMEOUT;
	
  while(I2C_GetFlagStatus(SENSORS_I2Cx, I2C_FLAG_BUSY)) // Added by Najoua 27/08/2008    
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	 
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
  /* Send slave address for write */
  I2C_Send7bitAddress(SENSORS_I2Cx, MPU6050_SLAVE_ADDRESS, I2C_Direction_Transmitter);

	I2CTimeout = I2CT_FLAG_TIMEOUT;
	 
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) 
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(SENSORS_I2Cx, ENABLE);

  /* Send the slave's internal address to write to */
  I2C_SendData(SENSORS_I2Cx, ReadAddr);  

	I2CTimeout = I2CT_FLAG_TIMEOUT;
	 
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
		
  /* Send slave address for read */
  I2C_Send7bitAddress(SENSORS_I2Cx, MPU6050_SLAVE_ADDRESS, I2C_Direction_Receiver);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	 
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
  
  /* While there is data to be read */
  while(NumByteToRead)  
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(SENSORS_I2Cx, DISABLE);
      
      /* Send STOP Condition */
      I2C_GenerateSTOP(SENSORS_I2Cx, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))  
    {      
      /* Read a byte from the slave */
      *pBuffer = I2C_ReceiveData(SENSORS_I2Cx);

      /* Point to the next location where the byte read will be saved */
      pBuffer++; 
      
      /* Decrement the read bytes counter */
      NumByteToRead--;        
    }   
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(SENSORS_I2Cx, ENABLE);
	
	return 1; //����������1
}


/**
  * @brief  Wait for slave Standby state 
  * @param  ��
  * @retval ��
  */
void I2C_WaitStandbyState(void)      
{
  vu16 SR1_Tmp = 0;

  do
  {
    /* Send START condition */
    I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);
    /* Read I2C1 SR1 register */
    SR1_Tmp = I2C_ReadRegister(SENSORS_I2Cx, I2C_Register_SR1);
    /* Send slave address for write */
    I2C_Send7bitAddress(SENSORS_I2Cx, MPU6050_SLAVE_ADDRESS, I2C_Direction_Transmitter);
  }while(!(I2C_ReadRegister(SENSORS_I2Cx, I2C_Register_SR1) & 0x0002));
  
  /* Clear AF flag */
  I2C_ClearFlag(SENSORS_I2Cx, I2C_FLAG_AF);
    /* STOP condition */    
    I2C_GenerateSTOP(SENSORS_I2Cx, ENABLE); 
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
static  uint8_t I2C_TIMEOUT_UserCallback(void)
{
  /* Block communication and all processes */
  MPU_ERROR("I2C Timeout error!"); 
  
  return 0;
}

/*********************************************END OF FILE**********************/

