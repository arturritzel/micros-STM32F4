#include "stm32f4xx.h"


int t(void) {
	int t = 0;
	for (int i=0; i != 100000; i++){  // espera ~100ms
		if((GPIOC->IDR&=0x1)!=0x1) t++;
	}

	if(t > 0) return 1;

}

int main(void)
{
  RCC->AHB1ENR=0x00000087;
  GPIOA->MODER=0x28000000;  // inicializa o modo debugger para a interface do ARM
  GPIOB->MODER=0x55000454;  // configura os pinos B1, B2, B3, B5, B12, B13, B14 e B15 com a função de saída
  GPIOC->MODER=0x00000000;  // configura os pinos C com função de entrada

  int seq = 1;

  while (1)
  {
	  switch(seq){
	  case 1:
		    GPIOB->ODR=0x00000000; // reseta
		  	if(t() == 1){ seq = 2; break; }

		  	GPIOB->ODR|=0x00000002;  // liga o pino 1;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR|=0x00000004;  // liga o pino 2;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR|=0x00000008;  // liga o pino 3;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR|=0x00000020;  // liga o pino 5;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR|=0x00001000;  // liga o pino 12;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR|=0x00002000;  // liga o pino 13;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR|=0x00004000;  // liga o pino 14;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR|=0x00008000;  // liga o pino 15;
		  	if(t() == 1){ seq = 2; break; }

		  	GPIOB->ODR&=0xFFFF7FFF;  // desliga o pino 15;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR&=0xFFFFBFFF;  // desliga o pino 14;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR&=0xFFFFDFFF;  // desliga o pino 13;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR&=0xFFFFEFFF;  // desliga o pino 12;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR&=0xFFFFFFDF;  // desliga o pino 5;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR&=0xFFFFFFF7;  // desliga o pino 3;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR&=0xFFFFFFFB;  // desliga o pino 2;
		  	if(t() == 1){ seq = 2; break; }
		  	GPIOB->ODR&=0xFFFFFFFD;  // desliga o pino 1;
		  	if(t() == 1){ seq = 2; break; }

	  case 2:
		    GPIOB->ODR=0x00000000; // reseta
		  	if(t() == 0){ seq = 1; break; }

		  	GPIOB->ODR|=0x00008000;  // liga o pino 15;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR|=0x00004000;  // liga o pino 14;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR|=0x00002000;  // liga o pino 13;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR|=0x00001000;  // liga o pino 12;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR|=0x00000020;  // liga o pino 5;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR|=0x00000008;  // liga o pino 3;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR|=0x00000004;  // liga o pino 2;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR|=0x00000002;  // liga o pino 1;
		  	if(t() == 0){ seq = 1; break; }

		  	GPIOB->ODR&=0xFFFFFFFD;  // desliga o pino 1;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR&=0xFFFFFFFB;  // desliga o pino 2;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR&=0xFFFFFFF7;  // desliga o pino 3;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR&=0xFFFFFFDF;  // desliga o pino 5;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR&=0xFFFFEFFF;  // desliga o pino 12;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR&=0xFFFFDFFF;  // desliga o pino 13;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR&=0xFFFFBFFF;  // desliga o pino 14;
		  	if(t() == 0){ seq = 1; break; }
		  	GPIOB->ODR&=0xFFFF7FFF;  // desliga o pino 15;
		  	if(t() == 0){ seq = 1; break; }
	  }

  }
}
