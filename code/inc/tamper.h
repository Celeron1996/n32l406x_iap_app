#ifndef TAMPER_H
#define TAMPER_H

#include "stdint.h"
#include "log.h"

/* gpio define : interrupt config */
#define TAMPER_IRQ_GPIO_PORT			GPIOA
#define TAMPER_IRQ_GPIO_PIN				GPIO_PIN_4
#define TAMPER_IRQ_GPIO_CLK_ENABLE()	do{RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);}while(0)
#define TAMPER_IRQ_GPIO_CLK_DISABLE()	do{RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, DISABLE);}while(0)
/* int EXIT */
#define TAMPER_IRQ_EXIT_SOURCE_PORT		GPIOA_PORT_SOURCE
#define TAMPER_IRQ_EXIT_SOURCE_PIN		GPIO_PIN_SOURCE4
#define TAMPER_IRQ_EXIT_LINE			EXTI_LINE4
/* int : Configure the NVIC Preemption Priority Bits */
#define TAMPER_IRQ_NVIC_IRQ_CHANNEL		EXTI4_IRQn
/* gpio exti call define */
#define tamper_irq_call						exti4_irqhandler_call


void tamper_init(void);
void tamper_process(void);



#endif
