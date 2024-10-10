#ifndef LOG_H__
#define LOG_H__

#include "stdio.h"
#include "stdint.h"
#include "n32l40x.h"

/* gpio define : uart tx */
#define LOG_TX_GPIO_PORT					GPIOC
#define LOG_TX_GPIO_PIN					GPIO_PIN_12
#define LOG_TX_GPIO_CLK_ENABLE()			do{RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);}while(0)
#define LOG_TX_GPIO_CLK_DISABLE()			do{RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, DISABLE);}while(0)
#define LOG_TX_GPIO_AF						GPIO_AF6_UART5

/* uart config define */
#define LOG_UART							UART5
#define LOG_UART_BAUDRATE					115200u
#define LOG_UART_CLK_ENABLE()				do{RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_UART5, ENABLE);}while(0)
#define LOG_UART_CLK_DISABLE()				do{RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_UART5, DISABLE);}while(0)


#define LOG				printf

#define USING_LOG

void log_init(void);
void log_deinit(void);





#endif
