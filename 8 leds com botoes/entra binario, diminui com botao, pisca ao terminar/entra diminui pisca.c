#include "stm32f4xx.h"

/*

led 1-7, respectivamente:
B1, B2, B3, B5, B12, B13, B14

entrada binario, em ordem:
PC0, PC1, PC2

botao:
PC3

*/

void t(void) {
	for (int i=0; i != 1500; i++);  // espera
}

void t2(void) {
	for (int i=0; i != 800000; i++);  // espera
}

void l(int led){
	if(led == 1) GPIOB->ODR|=0x00000002;  // liga o pino 1;
	if(led == 2) GPIOB->ODR|=0x00000004;  // liga o pino 2;
	if(led == 3) GPIOB->ODR|=0x00000008;  // liga o pino 3;
	if(led == 4) GPIOB->ODR|=0x00000020;  // liga o pino 5;
	if(led == 5) GPIOB->ODR|=0x00001000;  // liga o pino 12;
	if(led == 6) GPIOB->ODR|=0x00002000;  // liga o pino 13;
	if(led == 7) GPIOB->ODR|=0x00004000;  // liga o pino 14;
}

void dl(int led){
	if(led == 1) GPIOB->ODR&=~0x00000002;  // desliga o pino 1;
	if(led == 2) GPIOB->ODR&=~0x00000004;  // desliga o pino 2;
	if(led == 3) GPIOB->ODR&=~0x00000008;  // desliga o pino 3;
	if(led == 4) GPIOB->ODR&=~0x00000020;  // desliga o pino 5;
	if(led == 5) GPIOB->ODR&=~0x00001000;  // desliga o pino 12;
	if(led == 6) GPIOB->ODR&=~0x00002000;  // desliga o pino 13;
	if(led == 7) GPIOB->ODR&=~0x00004000;  // desliga o pino 14;
}

int main(void)
{
  RCC->AHB1ENR=0x00000087;  // habilita o clock de todas as GPIOs
  GPIOA->MODER=0x28000000;  // inicializa o modo debugger para a interface do ARM
  GPIOB->MODER=0x55000454;  // configura os pinos B1, B2, B3, B5, B12, B13, B14 e B15 com a função de saída
  GPIOC->MODER=0x00000000;  // configura os pinos C como entrada

  int p1, p2, p3, total;

  /*
   *  entrada em binario
   */

  GPIOB->ODR=0x00000000;  // reset;

  // testagem das entradas

  if((GPIOC->IDR&=0x1)==0x1){
	p1 = 1;
  } else p1 = 0;

  if((GPIOC->IDR&=0x2)==0x2){
	p2 = 1;
  } else p2 = 0;

  if((GPIOC->IDR&=0x4)==0x4){
	p3 = 1;
  } else p3 = 0;

  total = p1*1 + p2*2 + p3*4;

  switch(8-total){
  case 1: l(7);
  case 2: l(6);
  case 3: l(5);
  case 4: l(4);
  case 5: l(3);
  case 6: l(2);
  case 7: l(1);
  }

  int menos = 0;

  while(1){

	  if((GPIOC->IDR&=0x8)==0x8){
		  dl(total-menos);
		  menos++;
	  }
	  while((GPIOC->IDR&=0x8)==0x8);

	  t();

	  while(total-menos <= 0){
		  for(int i = 0; i < 7; i++) l(i+1);
		  t2();
		  for(int i = 0; i < 7; i++) dl(i+1);
		  t2();
	  }
  }
}
