oiiiiiiiiiii outra hora eu termino de comentar tudo!!!!!!!! minha aula vai começar agora

private variables:
```c
int ch2_ccr[4] = {1499, 1699, 1899, 2099}; // define as bordas de subida/descida dos pulsos do canal 2 (200 ARR = 2ms)
int ch2_atu = 0; 

float ch3_inicio = 0;
int ch3_ativo = 0;
```

main:
```c
  HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_2);
  HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_4);
```

interrupção:
```c
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim){
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
			ch2_atu++;
			if(ch2_atu > 3) ch2_atu = 0;

			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ch2_ccr[ch2_atu]);
		}

		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
			if(ch3_ativo == 1){
				ch3_inicio = ch3_inicio + 44;
				if(ch3_inicio > 2500) ch3_inicio = 0;
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, ch3_inicio);

				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 2520 - ch3_inicio);

				ch3_ativo = 0;
			}

			else{
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, ch3_inicio+400);

				ch3_ativo = 1;
			}
		}
}
```


- (ativar interrupção do timer)  
![p1](p1.png)    
![p2](p2.png)  
![p3](p3.png)
