#include "n32l40x.h"
#include "log.h"
#include "tamper.h"


void delay(uint32_t ms)
{
	volatile uint16_t cnt;
	
	while (ms--)
	{
		cnt = 5000;
		while (cnt--);
	}
}

int main(void)
{
	uint32_t counter = 0;
	
	SCB->VTOR = FLASH_BASE|0x2000;
	
	log_init();
	tamper_init();
	
	LOG("build in %s, %s\r\n", __DATE__, __TIME__);
	while (1)
	{
		LOG("counter = %d\r\n", counter++);
		delay(500);
		tamper_process();
	}
	
}


