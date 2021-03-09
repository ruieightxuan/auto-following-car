#include "uwb.h"
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
#include "motor.h"

uint8_t USART_RX_BUF[USART_REC_LEN];
uint16_t USART_RX_STA=0;       //接收状态标记	
uint8_t aRxBuffer[RXBUFFERSIZE];//HAL库使用的串口接收缓冲



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)//如果是串口1
	{
		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				else USART_RX_STA|=0x8000;	//接收完成了 
			}
			else //还没收到0X0D
			{	
				if(aRxBuffer[0]==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}

	}
}


void uwb_task(void *argument)
{
  /* USER CODE BEGIN uwb_task */
  /* Infinite loop */
  for(;;)
  {
   if(USART_RX_STA&0x8000)
		{					   
			length=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			uwb_index=0;
			uwb_index1=0;
			distl=0;
			distr=0;
			memcpy(uwb_dist,USART_RX_BUF,20*sizeof(uint8_t));
			for(int i=0;i<length;i++)
			{
			  if(uwb_dist[i]==','&&uwb_index==0)
				{
				uwb_index=i;
				}
				else if(uwb_dist[i]==','&&uwb_index!=0)
				{
				uwb_index1=i;
				}			
			}
			for(int i=uwb_index+1;i<uwb_index1;i++)
			{
			distl=distl*10+(uwb_dist[i]-'0');		//左边距离
			}
			for(int i=uwb_index1+1;i<length;i++)
			{
			distr=distr*10+(uwb_dist[i]-'0');   //右边距离
			}
			USART_RX_STA=0;
		}
		
		osDelay(10);
  }
  /* USER CODE END uwb_task */
}

