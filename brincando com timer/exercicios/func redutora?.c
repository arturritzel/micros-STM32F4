// nao sei no q eu tava pensando mas existem no minimo uns 50 jeitos mais simples de fazer isso

void t(int ms){
	int novoArr = (ms*16) - 1;
	while(novoArr > 65000){
		TIM11->ARR=65000;


		while((TIM11->SR&0x01) == 0x00);
		TIM11->SR&=~(0x01);

		novoArr -= 65000;
	}

	TIM11->ARR = novoArr;

	while((TIM11->SR&0x01) == 0x00);
	TIM11->SR&=~(0x01);
}
