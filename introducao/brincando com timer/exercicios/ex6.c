#include "stm32f4xx.h"

/*
 * timer 10: ira trabalhar com altas frequencias
 * psc arbitrado: 160
 *
 * timer 11: ira trabalhar com baixas frequencias
 * psc arbitrado: 16000
 */

int calculaArrEmFreq(float freq, float presc){
	float tempo = (1/freq)/2;
	return tempo*16000000/(presc+1);
}

void liga(int pino){ // funcao liga pino x (numero 1 a 8)
	switch(pino){
	case 1:
		GPIOB->ODR|=0x00000002;  // liga o pino 1;
		break;
	case 2:
		GPIOB->ODR|=0x00000004;  // liga o pino 2;
		break;
	case 3:
		GPIOB->ODR|=0x00000008;  // liga o pino 3;
		break;
	case 4:
		GPIOB->ODR|=0x00000020;  // liga o pino 5;
		break;
	case 5:
		GPIOB->ODR|=0x00001000;  // liga o pino 12;
		break;
	case 6:
		GPIOB->ODR|=0x00002000;  // liga o pino 13;
		break;
	case 7:
		GPIOB->ODR|=0x00004000;  // liga o pino 14;
		break;
	case 8:
		GPIOB->ODR|=0x00008000;  // liga o pino 15;
		break;
	}
}

void desliga(int pino){ // funcao desliga pino x (numero 1 a 8)
	switch(pino){
	case 1:
		GPIOB->ODR&=~0x00000002;  // desliga o pino 1;
		break;
	case 2:
		GPIOB->ODR&=~0x00000004;  // desliga o pino 2;
		break;
	case 3:
		GPIOB->ODR&=~0x00000008;  // desliga o pino 3;
		break;
	case 4:
		GPIOB->ODR&=~0x00000020;  // desliga o pino 5;
		break;
	case 5:
		GPIOB->ODR&=~0x00001000;  // desliga o pino 12;
		break;
	case 6:
		GPIOB->ODR&=~0x00002000;  // desliga o pino 13;
		break;
	case 7:
		GPIOB->ODR&=~0x00004000;  // desliga o pino 14;
		break;
	case 8:
		GPIOB->ODR&=~0x00008000;  // desliga o pino 15;
		break;
	}
}

void piscaED(){ // pisca esquerda direita
	for(int i = 0; i < 8; i++){
		liga(i+1);

		while((TIM11->SR&0x01) == 0x00);
		TIM11->SR&=~(0x01);
	}

	for(int i = 8; i > 0; i--){
		desliga(i);

		while((TIM11->SR&0x01) == 0x00);
		TIM11->SR&=~(0x01);
	}
}

int main(void)
{
	RCC->AHB1ENR=0x00000087;
	GPIOA->MODER=0x28000000;  // inicializa o modo debugger para a interface do ARM
	GPIOB->MODER=0x55000454;  // configura os pinos B1, B2, B3, B5, B12, B13, B14 e B15 com a função de saída
	GPIOC->MODER=0x00000000;  // configura os pinos C com função de entrada

	RCC->APB2ENR|=0x20000;
	RCC->APB2ENR|=0x40000;

	TIM10->PSC=159;
	TIM10->CR1=0x05;
	//TIM10->ARR=calculaArrEmFreq(5, TIM10->PSC);

	TIM11->PSC=15999;
	TIM11->CR1=0x05;
	//TIM11->ARR=calculaArrEmFreq(5, TIM11->PSC);
	TIM11->ARR=150;

	while (1){

		piscaED();

	}
}
