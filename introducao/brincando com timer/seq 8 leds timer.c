#include "stm32f4xx.h"


void t(void) {
	while((TIM10->SR&0x01) == 0x00);
	TIM10->SR&=~(0x01);
}

void seqed(){ // sequência esquerda direita
	GPIOB->ODR=0x00000000; // reseta

	GPIOB->ODR|=0x00000002;  // liga o pino 1;
	t();
	GPIOB->ODR|=0x00000004;  // liga o pino 2;
	t();
	GPIOB->ODR|=0x00000008;  // liga o pino 3;
	t();
	GPIOB->ODR|=0x00000020;  // liga o pino 5;
	t();
	GPIOB->ODR|=0x00001000;  // liga o pino 12;
	t();
	GPIOB->ODR|=0x00002000;  // liga o pino 13;
	t();
	GPIOB->ODR|=0x00004000;  // liga o pino 14;
	t();
	GPIOB->ODR|=0x00008000;  // liga o pino 15;
	t();

	GPIOB->ODR&=0xFFFF7FFF;  // desliga o pino 15;
	t();
	GPIOB->ODR&=0xFFFFBFFF;  // desliga o pino 14;
	t();
	GPIOB->ODR&=0xFFFFDFFF;  // desliga o pino 13;
	t();
	GPIOB->ODR&=0xFFFFEFFF;  // desliga o pino 12;
	t();
	GPIOB->ODR&=0xFFFFFFDF;  // desliga o pino 5;
	t();
	GPIOB->ODR&=0xFFFFFFF7;  // desliga o pino 3;
	t();
	GPIOB->ODR&=0xFFFFFFFB;  // desliga o pino 2;
	t();
	GPIOB->ODR&=0xFFFFFFFD;  // desliga o pino 1;
	t();
}

int main(void)
{
  RCC->AHB1ENR=0x87;
  GPIOA->MODER=0x28000000;  // inicializa o modo debugger para a interface do ARM
  GPIOB->MODER=0x55000454;  // configura os pinos B1, B2, B3, B5, B12, B13, B14 e B15 com a função de saída
  GPIOC->MODER=0x00000000;  // configura os pinos C com função de entrada

  RCC->APB2ENR|=0x20000;
  TIM10->CR1=0x05;
  TIM10->PSC=7999;
  TIM10->ARR=9999;


  while (1)
  {
	  seqed();


  }
}
