#include "tamper.h"


static volatile uint8_t tamper_irq_flag = 0;


void tamper_process(void)
{
	if (tamper_irq_flag)
	{
		tamper_irq_flag = 0;
		LOG("button active!\r\n");
	}
}

/**
	* @brief	tamper button init
	**/
void tamper_init(void)
{
	GPIO_InitType gpio_init;
	EXTI_InitType exti_init;
	NVIC_InitType nvic_init;
	
	/* config IRQ gpio */
	TAMPER_IRQ_GPIO_CLK_ENABLE();
	GPIO_InitStruct(&gpio_init);
	gpio_init.Pin 		= TAMPER_IRQ_GPIO_PIN;
	gpio_init.GPIO_Pull 	= GPIO_Pull_Up;
	gpio_init.GPIO_Mode 	= GPIO_Mode_IT_Rising_Falling;
	GPIO_InitPeripheral(TAMPER_IRQ_GPIO_PORT, &gpio_init);
	GPIO_ConfigEXTILine(TAMPER_IRQ_EXIT_SOURCE_PORT, TAMPER_IRQ_EXIT_SOURCE_PIN);

	/*Set IRQ interrupt priority*/
	nvic_init.NVIC_IRQChannel 									= TAMPER_IRQ_NVIC_IRQ_CHANNEL;
	nvic_init.NVIC_IRQChannelPreemptionPriority = 0x05;
	nvic_init.NVIC_IRQChannelSubPriority				= 0x0F;
	nvic_init.NVIC_IRQChannelCmd								= ENABLE;
	NVIC_Init(&nvic_init);

	/*Configure IRQ EXTI line*/
	EXTI_InitStruct(&exti_init);
	exti_init.EXTI_Line 	 = TAMPER_IRQ_EXIT_LINE;
	exti_init.EXTI_Mode 	 = EXTI_Mode_Interrupt;
	exti_init.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti_init.EXTI_LineCmd = ENABLE;
	EXTI_InitPeripheral(&exti_init);
}


/**
	* @brief	tamper IRQ
	**/
void tamper_irq_call(void)
{
	if(RESET != EXTI_GetITStatus(TAMPER_IRQ_EXIT_LINE))
	{
		tamper_irq_flag = 1;
		EXTI_ClrITPendBit(TAMPER_IRQ_EXIT_LINE);
	}
}



void EXTI4_IRQHandler(void)
{
	tamper_irq_call();
}

