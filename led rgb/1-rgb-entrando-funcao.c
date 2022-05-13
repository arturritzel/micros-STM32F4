#include "stm32f4xx.h"

int r = 1, g = 2, b = 3;

void t() {
	for (int i=0; i != 50; i++);  // delay
}

void t2(){
	for (int i=0; i != 50000; i++);  // delay
}

void t3(){
	for (int i=0; i != 500000; i++);  // delay
}

void cor(int intr, int intg, int intb){
	while(intr > 255) intr = 255;
	while(intg > 255) intg = 255;
	while(intb > 255) intb = 255;

	for(int i = 0; i < intr; i++){
		p(r);
	}

	for(int i = 0; i < intg; i++){
		p(g);
	}

	for(int i = 0; i < intb; i++){
		p(b);
	}

	for(int i = 0; i < 255; i++){
		t();
	}
}

void p(char cor){
	if(cor == 1){
		GPIOB->ODR&=0xFFFFFFFB;  // desliga o pino 2;
		t();
		GPIOB->ODR|=0x00000004;  // liga o pino 2;
	}

	if(cor == 2){
		GPIOB->ODR&=0xFFFFFFF7;  // desliga o pino 3;
		t();
		GPIOB->ODR|=0x00000008;  // liga o pino 3;
	}

	if(cor == 3){
		GPIOB->ODR&=0xFFFFFFDF;  // desliga o pino 5;
		t();
		GPIOB->ODR|=0x00000020;  // liga o pino 5;
	}
}

int main(void)
{
  RCC->AHB1ENR=0x00000087;
  GPIOA->MODER=0x28000000;  // inicializa o modo debugger para a interface do ARM
  GPIOB->MODER=0x55000454;  // configura os pinos B1, B2, B3, B5, B12, B13, B14 e B15 com a função de saída


  GPIOB->ODR|=0xFFFFFFFF;  // liga todos os pinos;

  while (1)
  {
	  cor(255,255,0);

  }
}
