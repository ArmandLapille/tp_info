#include "clock_config.h"
#include "gpio_init.h"
#include "init_UART.h"
#include "myPrint.h"
#include <stdio.h>
#include <string.h>
#include "arbre_de_Huffman.h"



int main(void)
{
  HAL_Init();
  SystemClock_Config();
  GPIO_Init();
  init_UART();

  arbre_de_Huffman();
  while(1){

  }
}



