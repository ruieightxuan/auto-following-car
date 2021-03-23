#include "main_control.h"
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
#include "motor.h"



float distl_ave = 0.0;
float distr_ave = 0.0;
float distlr_ave = 0.0;

int obstacle_count,count1;

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
		distr_ave = 0.5*(distr + last_distr);//uwb数据均值滤波
		distl_ave += 20;//为了使小车靠右行驶，给左边uwb数据加20，该数据可根据实际情况更改
		
		distlr_ave = (distl_ave + distr_ave)*0.5;

		deleta_origin=distr_ave-distl_ave;	//左右距离的差值
		last_distl = distl;
		last_distr = distr;
		
		/*模式控制begin*/
		//速度控制，即距离越大速度越快，采用分段函数方式进行控制
		if (distlr_ave<50) motor_speed_set(SPEED_VERY_LOW);
		else if ((distl_ave>50)&&(distl_ave<100)) motor_speed_set(SPEED_LOW);
		else if ((distl_ave>100)&&(distl_ave<150)) motor_speed_set(SPEED_MID);
		else if ((distl_ave>150)&&(distl_ave<200)) motor_speed_set(SPEED_HIGH);
		else 	motor_speed_set(SPEED_VERY_HIGH);
		
		
		if((lenM<60&&lenM>8)||(lenL<60&&lenL>8)||(lenR<60&&lenR>8))//测距模式
		{
			obstacle_count ++;
		}
		else
		{
			obstacle_count = 0;
		}
		
		if(obstacle_count>=5)	//连续检测到五次障碍物，为了消除抖动 
		//if(0) //如需开启避障，请把此行代码注释，并把上一行代码取消注释，反之
		{
			if(distr_ave==0&&distl_ave==20)
			{  
				//steer_control(0);
			   MOTOR_L_STOP
				 MOTOR_R_STOP
			}
			else
		{
			if(lenL<15||lenM<15||lenR<15)	//距离过小，停车
			{
				count1++;
				if(count1>=5)
				{MOTOR_L_STOP
				  MOTOR_R_STOP}
			}
			else 
			{
				count1=0; //防抖
					if(lenM<60)	//检测到障碍物，默认向右转
				 {
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(29);
				 }
				 else if((lenL<lenR)&&lenL<45) //左边存在障碍物，向右转
				{
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(29);
				}
				else if((lenL>lenR)&&lenR<45)	//右边存在障碍物，想左转
				{
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(-35);
				}
		  }
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
			if(distr_ave==0&&distl_ave==20)//当uwb离线时
			{  
				steer_control(0);
			   MOTOR_L_STOP
				 MOTOR_R_STOP
			}
			else
			steer_control(duoji);
		}
		osDelay(50);
  }
  /* USER CODE END main_control_task */
}

