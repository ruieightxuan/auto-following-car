#include "wave.h"
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
uint8_t  TIM3CH1_CAPTURE_STA=0;							//���벶��״̬		    				
uint8_t  TIM3CH2_CAPTURE_STA=0;							//���벶��״̬		    				
uint8_t  TIM3CH3_CAPTURE_STA=0;							//���벶��״̬		    				

uint16_t	TIM3CH1_CAPTURE_VAL;							  //���벶��ֵ(TIM3��16λ)
uint16_t	TIM3CH2_CAPTURE_VAL;							  //���벶��ֵ(TIM3��16λ)
uint16_t	TIM3CH3_CAPTURE_VAL;							  //���벶��ֵ(TIM3��16λ)


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//�����жϣ����������ʱִ��
{
//	if((TIM3CH1_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����������
//	{
//		if(TIM3CH1_CAPTURE_STA&0X40)				//�Ѿ����񵽸ߵ�ƽ��
//		{
//			if((TIM3CH1_CAPTURE_STA&0X3F)==0X3F)	//�ߵ�ƽ̫����
//			{
//				TIM3CH1_CAPTURE_STA|=0X80;			//��ǳɹ�������һ��
//				TIM3CH1_CAPTURE_VAL=0XFFFF;
//			}else TIM3CH1_CAPTURE_STA++;
//		}	 
//	}		
//	else if((TIM3CH2_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����������
//	{
//		if(TIM3CH2_CAPTURE_STA&0X40)				//�Ѿ����񵽸ߵ�ƽ��
//		{
//			if((TIM3CH2_CAPTURE_STA&0X3F)==0X3F)	//�ߵ�ƽ̫����
//			{
//				TIM3CH2_CAPTURE_STA|=0X80;			//��ǳɹ�������һ��
//				TIM3CH2_CAPTURE_VAL=0XFFFF;
//			}else TIM3CH2_CAPTURE_STA++;
//		}	 
//	}		
	if((TIM3CH3_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����������
	{
		if(TIM3CH3_CAPTURE_STA&0X40)				//�Ѿ����񵽸ߵ�ƽ��
		{
			if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)	//�ߵ�ƽ̫����
			{
				TIM3CH3_CAPTURE_STA|=0X80;			//��ǳɹ�������һ��
				TIM3CH3_CAPTURE_VAL=0XFFFF;
			}else TIM3CH3_CAPTURE_STA++;
		}	 
	}		
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//�����жϷ���ʱִ��
{
//	if((TIM3CH1_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
//	{
//		if(TIM3CH1_CAPTURE_STA&0X40)				//����һ���½��� 		
//		{	  			
//			TIM3CH1_CAPTURE_STA|=0X80;				//��ǳɹ�����һ�θߵ�ƽ����
//      TIM3CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
//			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
//      TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//����TIM3ͨ��3�����ز���
//		}else  										//��δ��ʼ,��һ�β���������
//		{
//			TIM3CH1_CAPTURE_STA=0;					//���
//			TIM3CH1_CAPTURE_VAL=0;
//			TIM3CH1_CAPTURE_STA|=0X40;				//��ǲ�����������
//			__HAL_TIM_DISABLE(&htim3);      	//�رն�ʱ��3
//			__HAL_TIM_SET_COUNTER(&htim3,0);
//			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
//			TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��3ͨ��3����Ϊ�½��ز���
//			__HAL_TIM_ENABLE(&htim3);		//ʹ�ܶ�ʱ��3
//		}		    
//	}		
//	else if((TIM3CH2_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
//	{
//		if(TIM3CH2_CAPTURE_STA&0X40)				//����һ���½��� 		
//		{	  			
//			TIM3CH2_CAPTURE_STA|=0X80;				//��ǳɹ�����һ�θߵ�ƽ����
//      TIM3CH2_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_2);//��ȡ��ǰ�Ĳ���ֵ.
//			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_2);   //һ��Ҫ�����ԭ�������ã���
//      TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);//����TIM3ͨ��3�����ز���
//		}else  										//��δ��ʼ,��һ�β���������
//		{
//			TIM3CH2_CAPTURE_STA=0;					//���
//			TIM3CH2_CAPTURE_VAL=0;
//			TIM3CH2_CAPTURE_STA|=0X40;				//��ǲ�����������
//			__HAL_TIM_DISABLE(&htim3);      	//�رն�ʱ��3
//			__HAL_TIM_SET_COUNTER(&htim3,0);
//			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_2);   //һ��Ҫ�����ԭ�������ã���
//			TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);//��ʱ��3ͨ��3����Ϊ�½��ز���
//			__HAL_TIM_ENABLE(&htim3);		//ʹ�ܶ�ʱ��3
//		}		    
//	}		
	if((TIM3CH3_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
	{
		if(TIM3CH3_CAPTURE_STA&0X40)				//����һ���½��� 		
		{	  			
			TIM3CH3_CAPTURE_STA|=0X80;				//��ǳɹ�����һ�θߵ�ƽ����
            TIM3CH3_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_3);//��ȡ��ǰ�Ĳ���ֵ.
			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_3);   //һ��Ҫ�����ԭ�������ã���
            TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_3,TIM_ICPOLARITY_RISING);//����TIM3ͨ��3�����ز���
		}else  										//��δ��ʼ,��һ�β���������
		{
			TIM3CH3_CAPTURE_STA=0;					//���
			TIM3CH3_CAPTURE_VAL=0;
			TIM3CH3_CAPTURE_STA|=0X40;				//��ǲ�����������
			__HAL_TIM_DISABLE(&htim3);      	//�رն�ʱ��3
			__HAL_TIM_SET_COUNTER(&htim3,0);
			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_3);   //һ��Ҫ�����ԭ�������ã���
			TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_3,TIM_ICPOLARITY_FALLING);//��ʱ��3ͨ��3����Ϊ�½��ز���
			__HAL_TIM_ENABLE(&htim3);		//ʹ�ܶ�ʱ��3
		}		    
	}		
}

void Trig_Init(void)
{
	HAL_GPIO_WritePin(GPIOB,WAVE_TRIGGER_LEFT_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,WAVE_TRIGGER_MID_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,WAVE_TRIGGER_RIGHT_Pin,GPIO_PIN_RESET);
}

void ch1_capture(void)
{    
			TRIG1h;
			delay_us(20);
			TRIG1l;
	    
}
void ch2_capture(void)
{    
			TRIG2h;
			delay_us(20);
			TRIG2l;
	   
}
void ch3_capture(void)
{    
			TRIG3h;
			delay_us(20);
			TRIG3l;

}

void delay_us(uint32_t udelay)
{
  uint32_t startval,tickn,delays,wait;
 
  startval = SysTick->VAL;
  tickn = HAL_GetTick();
  //sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
  delays =udelay * 72; //sysc / 1000 * udelay;
  if(delays > startval)
    {
      while(HAL_GetTick() == tickn)
        {
 
        }
      wait = 72000 + startval - delays;
      while(wait < SysTick->VAL)
        {
 
        }
    }
  else
    {
      wait = startval - delays;
      while(wait < SysTick->VAL && HAL_GetTick() == tickn)
        {
 
        }
    }
}

void wave_task(void *argument)
{
  /* USER CODE BEGIN wave_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
  }
  /* USER CODE END wave_task */
}














