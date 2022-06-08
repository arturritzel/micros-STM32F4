#include "stm32f4xx.h"
#include "time.h"

/*
 * display dos leds:
 * 1   12
 * 2 5 13
 * 3   14
 * */

void t(void) {
for (int i=0; i != 100000; i++);  // espera
}

void dado(int numligar){
	switch(numligar){
	case 1:
		GPIOB->ODR|=0x00000020;  // liga o pino 5;
		break;
	case 2:
		GPIOB->ODR|=0x00000002;  // liga o pino 1;
		GPIOB->ODR|=0x00004000;  // liga o pino 14;
		break;
	case 3:
		GPIOB->ODR|=0x00000002;  // liga o pino 1;
		GPIOB->ODR|=0x00000020;  // liga o pino 5;
		GPIOB->ODR|=0x00004000;  // liga o pino 14;
		break;
	case 4:
		GPIOB->ODR|=0x00000002;  // liga o pino 1;
		GPIOB->ODR|=0x00000008;  // liga o pino 3;
		GPIOB->ODR|=0x00001000;  // liga o pino 12;
		GPIOB->ODR|=0x00004000;  // liga o pino 14;
		break;
	case 5:
		GPIOB->ODR|=0x00000002;  // liga o pino 1;
		GPIOB->ODR|=0x00000008;  // liga o pino 3;
		GPIOB->ODR|=0x00000020;  // liga o pino 5;
		GPIOB->ODR|=0x00001000;  // liga o pino 12;
		GPIOB->ODR|=0x00004000;  // liga o pino 14;
		break;
	case 6:
		GPIOB->ODR|=0x00000002;  // liga o pino 1;
		GPIOB->ODR|=0x00000004;  // liga o pino 2;
		GPIOB->ODR|=0x00000008;  // liga o pino 3;
		GPIOB->ODR|=0x00001000;  // liga o pino 12;
		GPIOB->ODR|=0x00002000;  // liga o pino 13;
		GPIOB->ODR|=0x00004000;  // liga o pino 14;
		break;

	}
}                                          //*/

int main(void)
{
  srand(time(0));
  int numdado;
  RCC->AHB1ENR=0x00000087;
  GPIOA->MODER=0x28000000;  // inicializa o modo debugger para a interface do ARM
  GPIOB->MODER=0x55000454;  // configura os pinos B1, B2, B3, B5, B12, B13, B14 e B15 com a função de saída

  while (1)
  {
	  while((GPIOC->IDR&=0x2000)==0x2000){}
	  while((GPIOC->IDR&=0x2000)!=0x2000){}

	  GPIOB->ODR=0; // reseta
	  numdado = rand() % 6 + 1; // gera o numero do dado

	  dado(numdado); // liga o dadinho
  }
}
