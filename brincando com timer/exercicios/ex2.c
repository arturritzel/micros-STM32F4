#include "stm32f4xx.h"

/*
 * utilizar TIM10
 * PC1 como entrada, definindo se PB0 pisca (ligando um led quando PB0 high) a 2Hz (PC1 high) ou 7Hz (PC1 low)
 * botaozinho fofo no PC1 qnd aperta fica alto
 */

int main(void)
{
	RCC->AHB1ENR=0x87;
	GPIOC->MODER=0x00; // PC1 como entrada
	GPIOB->MODER=0x01;  // PB0 como saída

	RCC->APB2ENR|=0x20000;
	TIM10->CR1=0x05;
	TIM10->PSC=999;

	while (1) {
		if((GPIOC->IDR&=0x2)!=0x2){
			TIM10->ARR=1141;
		}
		else TIM10->ARR=3999;

		while((TIM10->SR&0x01) == 0x00);
		TIM10->SR&=~(0x01);

		GPIOB->ODR^=0x01; // inverte PB0

	}
}
