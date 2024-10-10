#include "log.h"



#ifdef USING_LOG 

void log_init(void)
{
	GPIO_InitType gpio_init;
	USART_InitType usart_init;
	
	/* step 1 enable gpio tx clk */
	LOG_TX_GPIO_CLK_ENABLE();

	/* step 2 enable uart clk */
	LOG_UART_CLK_ENABLE();

  /* step 3 gpio config */
  /* Initialize gpio_init */
  GPIO_InitStruct(&gpio_init);
  /* Configure USARTy Tx as alternate function push-pull */
  gpio_init.Pin            = LOG_TX_GPIO_PIN;    
  gpio_init.GPIO_Mode      = GPIO_Mode_AF_PP;
  gpio_init.GPIO_Alternate = LOG_TX_GPIO_AF;
  GPIO_InitPeripheral(LOG_TX_GPIO_PORT, &gpio_init);

  /* step 4 uart config */
  USART_StructInit(&usart_init);
  usart_init.BaudRate            = LOG_UART_BAUDRATE;
  usart_init.WordLength          = USART_WL_8B;
  usart_init.StopBits            = USART_STPB_1;
  usart_init.Parity              = USART_PE_NO;
  usart_init.HardwareFlowControl = USART_HFCTRL_NONE;
  usart_init.Mode                = USART_MODE_TX;
	USART_Init(LOG_UART, &usart_init);

	/* step 4.1 uart enable */
	USART_Enable(LOG_UART, ENABLE);
}


void log_deinit(void)
{
	GPIO_InitType gpio_init;

	USART_Enable(LOG_UART, DISABLE);

	USART_DeInit(LOG_UART);

	GPIO_InitStruct(&gpio_init);
	gpio_init.Pin        				= LOG_TX_GPIO_PIN;
	gpio_init.GPIO_Current 			= GPIO_DC_2mA;
	gpio_init.GPIO_Slew_Rate 			= GPIO_Slew_Rate_High;
	gpio_init.GPIO_Pull 				= GPIO_No_Pull;
	gpio_init.GPIO_Mode  				= GPIO_Mode_Out_PP;
	GPIO_InitPeripheral(LOG_TX_GPIO_PORT, &gpio_init);
}


int fputc(int ch, FILE* f)
{
    USART_SendData(LOG_UART, (uint8_t)ch);
    while (USART_GetFlagStatus(LOG_UART, USART_FLAG_TXDE) == RESET);

    return (ch);
}

#endif


