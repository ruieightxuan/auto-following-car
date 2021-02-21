#include "wave.h"
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
uint8_t  TIM3CH1_CAPTURE_STA=0;							//输入捕获状态		    				
uint8_t  TIM3CH2_CAPTURE_STA=0;							//输入捕获状态		    				
uint8_t  TIM3CH3_CAPTURE_STA=0;							//输入捕获状态		    				

uint16_t	TIM3CH1_CAPTURE_VAL;							  //输入捕获值(TIM3是16位)
uint16_t	TIM3CH2_CAPTURE_VAL;							  //输入捕获值(TIM3是16位)
uint16_t	TIM3CH3_CAPTURE_VAL;							  //输入捕获值(TIM3是16位)


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//更新中断（溢出）发生时执行
{
//	if((TIM3CH1_CAPTURE_STA&0X80)==0)				//还未成功捕获上升沿
//	{
//		if(TIM3CH1_CAPTURE_STA&0X40)				//已经捕获到高电平了
//		{
//			if((TIM3CH1_CAPTURE_STA&0X3F)==0X3F)	//高电平太长了
//			{
//				TIM3CH1_CAPTURE_STA|=0X80;			//标记成功捕获了一次
//				TIM3CH1_CAPTURE_VAL=0XFFFF;
//			}else TIM3CH1_CAPTURE_STA++;
//		}	 
//	}		
//	else if((TIM3CH2_CAPTURE_STA&0X80)==0)				//还未成功捕获上升沿
//	{
//		if(TIM3CH2_CAPTURE_STA&0X40)				//已经捕获到高电平了
//		{
//			if((TIM3CH2_CAPTURE_STA&0X3F)==0X3F)	//高电平太长了
//			{
//				TIM3CH2_CAPTURE_STA|=0X80;			//标记成功捕获了一次
//				TIM3CH2_CAPTURE_VAL=0XFFFF;
//			}else TIM3CH2_CAPTURE_STA++;
//		}	 
//	}		
	if((TIM3CH3_CAPTURE_STA&0X80)==0)				//还未成功捕获上升沿
	{
		if(TIM3CH3_CAPTURE_STA&0X40)				//已经捕获到高电平了
		{
			if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)	//高电平太长了
			{
				TIM3CH3_CAPTURE_STA|=0X80;			//标记成功捕获了一次
				TIM3CH3_CAPTURE_VAL=0XFFFF;
			}else TIM3CH3_CAPTURE_STA++;
		}	 
	}		
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//捕获中断发生时执行
{
//	if((TIM3CH1_CAPTURE_STA&0X80)==0)				//还未成功捕获
//	{
//		if(TIM3CH1_CAPTURE_STA&0X40)				//捕获到一个下降沿 		
//		{	  			
//			TIM3CH1_CAPTURE_STA|=0X80;				//标记成功捕获到一次高电平脉宽
//      TIM3CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);//获取当前的捕获值.
//			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1);   //一定要先清除原来的设置！！
//      TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//配置TIM3通道3上升沿捕获
//		}else  										//还未开始,第一次捕获上升沿
//		{
//			TIM3CH1_CAPTURE_STA=0;					//清空
//			TIM3CH1_CAPTURE_VAL=0;
//			TIM3CH1_CAPTURE_STA|=0X40;				//标记捕获到了上升沿
//			__HAL_TIM_DISABLE(&htim3);      	//关闭定时器3
//			__HAL_TIM_SET_COUNTER(&htim3,0);
//			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1);   //一定要先清除原来的设置！！
//			TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//定时器3通道3设置为下降沿捕获
//			__HAL_TIM_ENABLE(&htim3);		//使能定时器3
//		}		    
//	}		
//	else if((TIM3CH2_CAPTURE_STA&0X80)==0)				//还未成功捕获
//	{
//		if(TIM3CH2_CAPTURE_STA&0X40)				//捕获到一个下降沿 		
//		{	  			
//			TIM3CH2_CAPTURE_STA|=0X80;				//标记成功捕获到一次高电平脉宽
//      TIM3CH2_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_2);//获取当前的捕获值.
//			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_2);   //一定要先清除原来的设置！！
//      TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);//配置TIM3通道3上升沿捕获
//		}else  										//还未开始,第一次捕获上升沿
//		{
//			TIM3CH2_CAPTURE_STA=0;					//清空
//			TIM3CH2_CAPTURE_VAL=0;
//			TIM3CH2_CAPTURE_STA|=0X40;				//标记捕获到了上升沿
//			__HAL_TIM_DISABLE(&htim3);      	//关闭定时器3
//			__HAL_TIM_SET_COUNTER(&htim3,0);
//			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_2);   //一定要先清除原来的设置！！
//			TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);//定时器3通道3设置为下降沿捕获
//			__HAL_TIM_ENABLE(&htim3);		//使能定时器3
//		}		    
//	}		
	if((TIM3CH3_CAPTURE_STA&0X80)==0)				//还未成功捕获
	{
		if(TIM3CH3_CAPTURE_STA&0X40)				//捕获到一个下降沿 		
		{	  			
			TIM3CH3_CAPTURE_STA|=0X80;				//标记成功捕获到一次高电平脉宽
            TIM3CH3_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_3);//获取当前的捕获值.
			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_3);   //一定要先清除原来的设置！！
            TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_3,TIM_ICPOLARITY_RISING);//配置TIM3通道3上升沿捕获
		}else  										//还未开始,第一次捕获上升沿
		{
			TIM3CH3_CAPTURE_STA=0;					//清空
			TIM3CH3_CAPTURE_VAL=0;
			TIM3CH3_CAPTURE_STA|=0X40;				//标记捕获到了上升沿
			__HAL_TIM_DISABLE(&htim3);      	//关闭定时器3
			__HAL_TIM_SET_COUNTER(&htim3,0);
			TIM_RESET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_3);   //一定要先清除原来的设置！！
			TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_3,TIM_ICPOLARITY_FALLING);//定时器3通道3设置为下降沿捕获
			__HAL_TIM_ENABLE(&htim3);		//使能定时器3
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














