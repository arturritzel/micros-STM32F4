#include "stm32f4xx.h"


void t(void) {
	for (int i=0; i != 200000; i++);  // espera ~100ms
}

int main(void)
{
  RCC->AHB1ENR=0x00000087;
  GPIOA->MODER=0x28000000;  // inicializa o modo debugger para a interface do ARM
  GPIOB->MODER=0x55000454;  // configura os pinos B1, B2, B3, B5, B12, B13, B14 e B15 com a função de saída

  int nled = 0;

  while (1)
  {


	  if((GPIOC->IDR&=0x2000)!=0x2000){
		  nled++;
		  if(nled > 8){
			  nled = 0;
		  }
	  }
	  while((GPIOC->IDR&=0x2000)!=0x2000){

	  }

	  GPIOB->ODR&=0x00000000;  // reset;

	  switch(9-nled){
	  case 1:
		  GPIOB->ODR|=0x00000002;  // liga o pino 1;
	  case 2:
		  GPIOB->ODR|=0x00000004;  // liga o pino 2;
	  case 3:
		  GPIOB->ODR|=0x00000008;  // liga o pino 3;
	  case 4:
		  GPIOB->ODR|=0x00000020;  // liga o pino 5;
	  case 5:
		  GPIOB->ODR|=0x00001000;  // liga o pino 12;
	  case 6:
		  GPIOB->ODR|=0x00002000;  // liga o pino 13;
	  case 7:
		  GPIOB->ODR|=0x00004000;  // liga o pino 14;
	  case 8:
		  GPIOB->ODR|=0x00008000;  // liga o pino 15;
	  }

	  t();
  }
}
