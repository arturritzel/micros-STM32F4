void t(int ms){
	int arrQ = (ms*16) - 1;
	while(arrQ > 65000){
		TIM11->ARR=65000;


		while((TIM11->SR&0x01) == 0x00);
		TIM11->SR&=~(0x01);

		arrQ -= 65000;
	}

	TIM11->ARR = arrQ;

	while((TIM11->SR&0x01) == 0x00);
	TIM11->SR&=~(0x01);
}
