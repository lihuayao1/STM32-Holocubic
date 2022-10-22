/*********************************************************************
File    : gpio.h
Purpose : 
**********************************************************************/

#ifndef __GPIO_H__
#define __GPIO_H__

/************************** Includes ***********************************/
/****************************** Defines *******************************/
#define ENABLE_INV_INTERRUPTS  EnableInvInterrupt()
#define DISABLE_INV_INTERRUPTS DisableInvInterrupt()


/***************************Globals *******************************************/
/***************************** Prototypes *****************************/
void GPIO_Config(void);
void EnableInvInterrupt(void);
void DisableInvInterrupt(void);
#endif // __GPIO_H__

