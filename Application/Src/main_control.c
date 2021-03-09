#include "main_control.h"
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
#include "motor.h"



float distl_ave = 0.0;
float distr_ave = 0.0;
float distlr_ave = 0.0;

float deleta=0;
float deleta_origin=0;
float duoji=0;
int speed_datio=0;

void main_control_task(void *argument)
{
  /* USER CODE BEGIN main_control_task */
  /* Infinite loop */
	
  for(;;)
  {
		/*数据获取begin*/
		
		distl_ave = 0.5*(distl + last_distl);
		distr_ave = 0.5*(distr + last_distr);
		distl_ave += 20;
		
		distlr_ave = (distl_ave + distr_ave)*0.5;

		deleta_origin=distr_ave-distl_ave;	//左右距离的差值
		last_distl = distl;
		last_distr = distr;
		
		/*模式控制begin*/
		//速度控制
		if (distlr_ave<50) motor_speed_set(SPEED_VERY_LOW);
		else if ((distl_ave>50)&&(distl_ave<100)) motor_speed_set(SPEED_LOW);
		else if ((distl_ave>100)&&(distl_ave<150)) motor_speed_set(SPEED_MID);
		else if ((distl_ave>150)&&(distl_ave<200)) motor_speed_set(SPEED_HIGH);
		else 	motor_speed_set(SPEED_VERY_HIGH);
		
		
		if((lenM<50&&lenM>8)||(lenL<50&&lenL>25.5)||(lenR<50&&lenR>10))//测距模式
		//if(0)
		{
			if(lenL<10||lenM<10||lenR<10)	//距离过小，停车
			{
					MOTOR_L_STOP
				  MOTOR_R_STOP
			}
			else 
			{
					if(lenM<30)	//检测到障碍物，默认向右转
				 {
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(20);
				 }
				 else if(lenL<lenR) //左边存在障碍物，向右转
				{
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(20);
				}
				else if(lenL>lenR)	//右边存在障碍物，想左转
				{
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(-24);
				}
		  }
			if(distr_ave==0&&distl_ave==20)
			{  
				steer_control(0);
			   MOTOR_L_STOP
				 MOTOR_R_STOP
			}
		}
		else//uwb模式
		{
			MOTOR_L_FORWARD
			MOTOR_R_FORWARD
			
			if(distlr_ave<100) duoji=-deleta_origin*1; //误差折算成角度,距离越近，偏转系数越大
			else if ((distl_ave>100)&&(distl_ave<200))  duoji=-deleta_origin*0.8; 
			else duoji=-deleta_origin*0.6; 
			
			if(duoji<0)duoji*=1.2;		//舵机误差校正,向左偏的时候不太灵敏
			
			//舵机限幅
			if(duoji>29) duoji=29;		
			else if(duoji<-37) duoji=-37;
			if(distr_ave==0&&distl_ave==20)
			{  
				steer_control(0);
			   MOTOR_L_STOP
				 MOTOR_R_STOP
			}
			else
			steer_control(duoji);
		}
		osDelay(10);
  }
  /* USER CODE END main_control_task */
}

