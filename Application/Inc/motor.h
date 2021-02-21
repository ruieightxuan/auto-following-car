#ifndef __MOTOR__H
#define __MOTOR__H
#include "main.h"
//Left motor control 
#define MOTOR_L_FORWARD {HAL_GPIO_WritePin(GPIOA, MOTOR_IN1_Pin, GPIO_PIN_RESET); HAL_GPIO_WritePin(GPIOA, MOTOR_IN2_Pin, GPIO_PIN_SET);}
#define MOTOR_L_STOP 			HAL_GPIO_WritePin(GPIOA, MOTOR_IN1_Pin|MOTOR_IN2_Pin, GPIO_PIN_SET);
#define MOTOR_L_BACKWARD {HAL_GPIO_WritePin(GPIOA, MOTOR_IN1_Pin, GPIO_PIN_SET); HAL_GPIO_WritePin(GPIOA, MOTOR_IN2_Pin, GPIO_PIN_RESET);}
//Right motor control
#define MOTOR_R_FORWARD {HAL_GPIO_WritePin(GPIOA, MOTOR_IN3_Pin, GPIO_PIN_RESET); HAL_GPIO_WritePin(GPIOA, MOTOR_IN4_Pin, GPIO_PIN_SET);}
#define MOTOR_R_STOP 			HAL_GPIO_WritePin(GPIOA, MOTOR_IN3_Pin|MOTOR_IN4_Pin, GPIO_PIN_SET);
#define MOTOR_R_BACKWARD {HAL_GPIO_WritePin(GPIOA, MOTOR_IN3_Pin, GPIO_PIN_SET); HAL_GPIO_WritePin(GPIOA, MOTOR_IN4_Pin, GPIO_PIN_RESET);}


#define SPEED_VERY_LOW 1  //cannot move
#define SPEED_LOW 2
#define SPEED_MID 3
#define SPEED_HIGH 4
#define SPEED_VERY_HIGH 5

void motor_init(void);
void motor_speed_set(unsigned int speed);

void steer_control(float angle);
#endif
