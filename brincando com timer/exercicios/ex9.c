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

void piscaPor(float freqPiscada){
	TIM10->ARR=calculaArrEmFreq(freqPiscada,TIM10->PSC);
	while((TIM11->SR&0x01) == 0x00){

		GPIOC->ODR^=0x02;

		while((TIM10->SR&0x01) == 0x00);
		TIM10->SR&=~(0x01);
	}

	TIM11->SR&=~(0x01);
}

int main(void)
{
	RCC->AHB1ENR=0x00000087;
	GPIOA->MODER=0x28000000;  // inicializa o modo debugger para a interface do ARM
	GPIOB->MODER=0x55000454;  // configura os pinos B1, B2, B3, B5, B12, B13, B14 e B15 com a função de saída
	GPIOC->MODER=0x00000004;  // configura PC1 como saída e outros C com função de entrada

	RCC->APB2ENR|=0x20000;
	RCC->APB2ENR|=0x40000;

	TIM10->PSC=159;
	TIM10->CR1=0x05;
	TIM10->ARR=calculaArrEmFreq(400,TIM10->PSC); // 1 segundo total

	TIM11->PSC=15999;
	TIM11->CR1=0x05;
	//TIM11->ARR=999; // 1 segundo total
	TIM11->ARR=calculaArrEmFreq(0.5,TIM11->PSC); // 1 segundo total

	while (1){

		piscaPor(261.63);
		piscaPor(293.66);
		piscaPor(329.63);
		piscaPor(349.23);
		piscaPor(392);
		piscaPor(440);
		piscaPor(493.88);

	}
}
