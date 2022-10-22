#ifndef __EXTI_H
#define	__EXTI_H


#include "stm32f10x.h"


/*外部中断EXIT相关宏定义*/
#define             EXTI_GPIO_CLK                        (RCC_APB2Periph_GPIOF|RCC_APB2Periph_AFIO)     
#define             EXTI_GPIO_PORT                       GPIOF   
#define             EXTI_GPIO_PIN                        GPIO_Pin_7
#define             EXTI_SOURCE_PORT                     GPIO_PortSourceGPIOF
#define             EXTI_SOURCE_PIN                      GPIO_PinSource7
#define             EXTI_LINE                            EXTI_Line7
#define             EXTI_IRQ                             EXTI9_5_IRQn
#define             EXTI_INT_FUNCTION                    EXTI9_5_IRQHandler


#define ENABLE_INV_INTERRUPTS  EnableInvInterrupt()
#define DISABLE_INV_INTERRUPTS DisableInvInterrupt()


void EXTI_Pxy_Config(void);
void EnableInvInterrupt(void);
void DisableInvInterrupt(void);


#endif /* __EXTI_H */

