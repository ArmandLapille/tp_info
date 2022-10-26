#include "myPrint.h"
#include <string.h>

#define TOGGLE_BIT(REG, BIT)  (REG^=(1<<BIT));
//#define SET_BIT(REG, BIT)

void myPrintf(uint8_t * text)
{
	for (int i=0; i< strlen(text); i++)
	{
		 /* tant que le bit TXE du registre SR de l'UART2 est != 1 --> attente de la fin de transmission du char précéd */
		 CLEAR_REG(USART2->DR);
		 USART2->DR = text[i];
		 while (USART2->SR &= (1<<7) ==0);
		 HAL_Delay(500);
		 TOGGLE_BIT(GPIOA->ODR,5);
	}
    /* boucle for qui permet de passer successivement les char de la chaine de char, sous forme de tableau*/
}
