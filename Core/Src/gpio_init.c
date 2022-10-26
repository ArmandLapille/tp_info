#include "gpio_init.h"

void GPIO_Init(void){
	__GPIOA_CLK_ENABLE();
	HAL_Delay(1);
	GPIOA->MODER |= (1<<10);
}
