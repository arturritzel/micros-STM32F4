/*
como o led deve ser ligado em low, ele deve ser polarizado reversamente. a malha é:
3v3 -> resistor e led -> PC0 atuando como "gnd"

	 *	0,2s = 1/1m6 * arr * psc
	 *	3200000 = arr * psc
	 *	psc = 1000
	 *	arr = 1600
	 */

#include "stm32f4xx.h"

int main(void)
{
	RCC->AHB1ENR=0x87;
	GPIOC->MODER=0x01; // C0 como saida

	RCC->APB2ENR|=0x40000;
	TIM11->CR1=0x05;
	TIM11->PSC=999;
	TIM11->ARR=1599;

	while (1) {

		GPIOC->ODR^=0x01; // inverte PC0

		while((TIM11->SR&0x01) == 0x00);
		TIM11->SR&=~(0x01);

	}
}
