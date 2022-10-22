#ifndef __EXTI_H
#define	__EXTI_H


#include "stm32f10x.h"


/*外部中断EXIT相关宏定义*/
#define             EXTI_GPIO_CLK                        (RCC_APB2Periph_GPIOA )     
#define             EXTI_GPIO_PORT                       GPIOA   
#define             EXTI_GPIO_PIN                        GPIO_Pin_11
#define             EXTI_SOURCE_PORT                     GPIO_PortSourceGPIOA
#define             EXTI_SOURCE_PIN                      GPIO_PinSource11
#define             EXTI_LINE                            EXTI_Line11
#define             EXTI_IRQ                             EXTI15_10_IRQn
#define             EXTI_INT_FUNCTION                    EXTI15_10_IRQHandler


#define ENABLE_INV_INTERRUPTS  EnableInvInterrupt()
#define DISABLE_INV_INTERRUPTS DisableInvInterrupt()


void EXTI_Pxy_Config(void);
void EnableInvInterrupt(void);
void DisableInvInterrupt(void);


#endif /* __EXTI_H */

