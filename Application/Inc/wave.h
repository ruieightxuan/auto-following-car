#ifndef __WAVE__H
#define __WAVE__H
#include "stm32f1xx_hal.h"
#include "main.h"


#define TRIG1l HAL_GPIO_WritePin(GPIOB,WAVE_TRIGGER_LEFT_Pin,GPIO_PIN_RESET)
#define TRIG2l HAL_GPIO_WritePin(GPIOB,WAVE_TRIGGER_MID_Pin,GPIO_PIN_RESET)
#define TRIG3l HAL_GPIO_WritePin(GPIOB,WAVE_TRIGGER_RIGHT_Pin,GPIO_PIN_RESET)

#define TRIG1h HAL_GPIO_WritePin(GPIOB,WAVE_TRIGGER_LEFT_Pin,GPIO_PIN_SET)
#define TRIG2h HAL_GPIO_WritePin(GPIOB,WAVE_TRIGGER_MID_Pin,GPIO_PIN_SET)
#define TRIG3h HAL_GPIO_WritePin(GPIOB,WAVE_TRIGGER_RIGHT_Pin,GPIO_PIN_SET)

void Trig_Init(void);

void ch1_capture(void);
void ch2_capture(void);
void ch3_capture(void);
void delay_us(uint32_t udelay);


extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern uint8_t  TIM3CH1_CAPTURE_STA;							//输入捕获状态		    				
extern uint8_t  TIM3CH2_CAPTURE_STA;							//输入捕获状态		    				
extern uint8_t  TIM3CH3_CAPTURE_STA;							//输入捕获状态		    				

extern uint16_t	TIM3CH1_CAPTURE_VAL;							  //输入捕获值(TIM3是16位)
extern uint16_t	TIM3CH2_CAPTURE_VAL;							  //输入捕获值(TIM3是16位)
extern uint16_t	TIM3CH3_CAPTURE_VAL;							  //输入捕获值(TIM3是16位)




#endif
