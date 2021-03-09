#include "main_control.h"
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
#include "motor.h"

float x_distl=0;
float x_distr=0;

float distl_ave = 0.0;
float distr_ave = 0.0;
float distlr_ave = 0.0;
float deleta=0;
float deleta_origin=0;
float duoji=0;

void main_control_task(void *argument)
{
  /* USER CODE BEGIN main_control_task */
  /* Infinite loop */
  for(;;)
  {
		/*���ݻ�ȡbegin*/
		
		distl_ave = 0.5*(distl + last_distl);
		distr_ave = 0.5*(distr + last_distr);
		//distl_ave += 20;
		
		distlr_ave = (distl_ave + distr_ave)*0.5;
    x_distl=sqrt((distl_ave*distl_ave-6400));
		x_distr=sqrt((distr_ave*distr_ave-6400));
		deleta=x_distr-x_distl;
		deleta_origin=distr_ave-distl_ave;
		last_distl = distl;
		last_distr = distr;
		
		/*ģʽ����begin*/
		//�ٶȿ���
		if (distlr_ave<150)
		{
			motor_speed_set(SPEED_MID);
		}
		else if ((distl_ave>150)&&(distl_ave<300))
		{
			motor_speed_set(SPEED_HIGH);
		}
		else 
		{
			motor_speed_set(SPEED_VERY_HIGH);
		}
		
		if((lenM<50&&lenM>8)||(lenL<50&&lenL>25.5)||(lenR<50&&lenR>10))//���ģʽ
		{
			if(lenL<10||lenM<10||lenR<10)	//�����С��ͣ��
			{
					MOTOR_L_STOP
				  MOTOR_R_STOP
			}
			else 
			{
					if(lenM<30)	//��⵽�ϰ��Ĭ������ת
				 {
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(20);
				 }
				 else if(lenL<lenR) //��ߴ����ϰ������ת
				{
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(20);
				}
				else if(lenL>lenR)	//�ұߴ����ϰ������ת
				{
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(-24);
				}
		  }
		}
		else//uwbģʽ
		{
			MOTOR_L_FORWARD
			MOTOR_R_FORWARD
			
			duoji=-deleta_origin*0.5; //�������ɽǶ�
			if(duoji<0)duoji*=1.2;		//������У��
			//����޷�
			if(duoji>29) duoji=29;		
			else if(duoji<-37) duoji=-37;
			steer_control(duoji);
		}
		osDelay(10);
  }
  /* USER CODE END main_control_task */
}

