main:
```
  HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_1);
```

interrupção:
```c
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			if(__HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_1) == 0)
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 99); // -> calculo abaixo
			else
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
		}
	}
}
```

16800 PSC * 10000 ARR / 84000000 SYSCLK = ciclo de 2s

se 10000 ARR = 2s, 20ms = X CCR

x = 0,02 * 10000 / 2 = 100





- (ativar interrupção)  
![31](31.png)    
![32](32.png)  
