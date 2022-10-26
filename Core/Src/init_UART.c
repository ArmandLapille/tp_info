#include "init_UART.h"

void init_UART(void)
{
	__USART2_CLK_ENABLE();
	GPIOA->MODER |= (0b10<<4); // Assignation de PA2 à la fonction TX de l'UART2
	GPIOA->AFR[0] |= (7<<8); // Définition de l'alternate function UART2
	USART2->CR1 |= USART_CR1_UE | USART_CR1_TE; // Activation de l'UART2
	USART2->BRR = 0x8B; // Configuration du registre BRR pour avoir un baud rate à 115200
}

int __io_putchar(int ch){
	WRITE_REG(USART2->DR,ch);
	while (READ_BIT(USART2->SR, 1<<7) == 0);
} // fonction qui permet d'activer le printf sur l'UART2
