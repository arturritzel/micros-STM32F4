#include "stm32f4xx.h"

/*
 * timer 10: ira trabalhar com altas frequencias
 * psc arbitrado: 160
 *
 * timer 11: ira trabalhar com baixas frequencias
 * psc arbitrado: 16000
 */

enum{
	Do = 262,
	Re = 294,
	Mi = 330,
	Fa = 349,
	Sol = 392,
	La = 440,
	Si = 494
};

int calculaArrEmFreq(float freq, float presc){
	float tempo = (1/freq)/2;
	return tempo*16000000/(presc+1);
}

void piscaPor(float freqPiscada){
	if(freqPiscada != 0)
		TIM10->ARR=calculaArrEmFreq(freqPiscada,TIM10->PSC);
	else TIM10->ARR=calculaArrEmFreq(100,TIM10->PSC);

	while((TIM11->SR&0x01) == 0x00){

		if(freqPiscada != 0)
			GPIOC->ODR^=0x02;

		while((TIM10->SR&0x01) == 0x00);
		TIM10->SR&=~(0x01);
	}

	TIM11->SR&=~(0x01);
}

int main(void)
{
	float OdeToJoy[] = {
						0, Mi, Mi, Fa, Sol, Sol, Fa, Mi, Re, Do, Do, Re,
						Mi, Mi, 0, Re, Re, 0, Mi, Mi, Fa, Sol, Sol, Fa,
						Mi, Re, Do, Do, Re, Mi, Re, 0, Do, Do, 0/*, Re, Mi,
						Do, Re, 0, Mi, Fa, Mi, Do, Re, Mi, Fa, Mi, Re,
						Do, Re, Sol, 0, Mi, Mi, Fa, Sol, Sol, Fa, Mi, Re,
						Do, Do, Re, Mi, Re, Do, Do
						*/
						};

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
	TIM11->ARR=calculaArrEmFreq(1,TIM11->PSC); // 0.5 segundo total

	for(int i = 0; i < sizeof(OdeToJoy)/sizeof(OdeToJoy[0]); i++){

		piscaPor(OdeToJoy[i]);

		TIM11->ARR=calculaArrEmFreq(10,TIM11->PSC);
		piscaPor(0);
		TIM11->ARR=calculaArrEmFreq(1,TIM11->PSC);

	}

}
