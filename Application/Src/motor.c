#include "motor.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
extern TIM_HandleTypeDef htim1;

void motor_init(void)
{
	//All motor stop
	HAL_GPIO_WritePin(GPIOA, MOTOR_IN1_Pin|MOTOR_IN2_Pin|MOTOR_IN3_Pin|MOTOR_IN4_Pin, GPIO_PIN_RESET); 
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);	//Left motor speed control
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);	//Right motor speed control
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);	
}

void motor_speed_set(unsigned int speed)
{
	if 	(speed == SPEED_VERY_LOW)
	{
		__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,6000);	//very slow 
		__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,6000);
	}
	else
	{
		__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,speed*4000);	//20000/5 = 4000 FULL SPEED:20000
		__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,speed*4000);
	}
}
// range: -30 to 30 
void steer_control(int angle)
{
	int offset = angle*500/45;
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,1500 + offset);
}

void motor_control_task(void *argument)
{
  /* USER CODE BEGIN motor_control_task */
  /* Infinite loop */
  for(;;)
  {	
		motor_speed_set(SPEED_VERY_LOW);
		MOTOR_L_FORWARD
		MOTOR_R_FORWARD
		steer_control(0);
    osDelay(10);
  }
  /* USER CODE END motor_control_task */
}
