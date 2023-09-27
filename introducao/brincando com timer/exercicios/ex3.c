/*
PB3, PB4 e PB5 como entrada em binario
saída PA8

caso entrada = 0, led aceso
caso entrada entre 1 e 5, pisca quantidade de vezes (100ms ligado e 100ms desligado)
1s total no tempo de piscada (mesmo q nao esteja piscando coisa)

	 *	0,1s = 1/1m6 * arr * psc
	 *	160000 = arr * 1600
	 *	psc = 1600
	 *	arr = 1000
	 */

#include "stm32f4xx.h"

int main(void)
{
	RCC->AHB1ENR=0x87; // inicializa todos os clocks
	GPIOA->MODER=0x28555500; // A como saida
	GPIOB->MODER=0; // B como entrada



	RCC->APB2ENR|=0x40000; // inicializa TIM11
	TIM11->CR1=0x05;
	TIM11->PSC=1599;
	TIM11->ARR=999; // total 100ms

	int entrada = 0;

	while (1) {
		while((TIM11->SR&0x01) == 0x00);
		TIM11->SR&=~(0x01);

		entrada = 0;

		if((GPIOB->IDR&=0x20)==0x20) entrada+=1;
		if((GPIOB->IDR&=0x10)==0x10) entrada+=2;
		if((GPIOB->IDR&=0x08)==0x08) entrada+=4;


		for(int i = 0; i < 5; i++){
			if(entrada == 0) GPIOA->ODR|=0x100;
			if(entrada > i) GPIOA->ODR|=0x100;

			while((TIM11->SR&0x01) == 0x00);
			TIM11->SR&=~(0x01);

			if(entrada > 0) GPIOA->ODR&=~0x100;

			while((TIM11->SR&0x01) == 0x00);
			TIM11->SR&=~(0x01);
		}

		GPIOA->ODR&=~0x100;

		for(int i = 0; i < 10; i++){
			while((TIM11->SR&0x01) == 0x00);
			TIM11->SR&=~(0x01);
		}


	}
}
