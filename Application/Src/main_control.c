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
		/*���ݻ�ȡbegin*/
		
		distl_ave = 0.5*(distl + last_distl);
		distr_ave = 0.5*(distr + last_distr);//uwb���ݾ�ֵ�˲�
		distl_ave += 20;//Ϊ��ʹС��������ʻ�������uwb���ݼ�20�������ݿɸ���ʵ���������
		
		distlr_ave = (distl_ave + distr_ave)*0.5;

		deleta_origin=distr_ave-distl_ave;	//���Ҿ���Ĳ�ֵ
		last_distl = distl;
		last_distr = distr;
		
		/*ģʽ����begin*/
		//�ٶȿ��ƣ�������Խ���ٶ�Խ�죬���÷ֶκ�����ʽ���п���
		if (distlr_ave<50) motor_speed_set(SPEED_VERY_LOW);
		else if ((distl_ave>50)&&(distl_ave<100)) motor_speed_set(SPEED_LOW);
		else if ((distl_ave>100)&&(distl_ave<150)) motor_speed_set(SPEED_MID);
		else if ((distl_ave>150)&&(distl_ave<200)) motor_speed_set(SPEED_HIGH);
		else 	motor_speed_set(SPEED_VERY_HIGH);
		
		
		if((lenM<60&&lenM>8)||(lenL<60&&lenL>8)||(lenR<60&&lenR>8))//���ģʽ
		{
			obstacle_count ++;
		}
		else
		{
			obstacle_count = 0;
		}
		
		if(obstacle_count>=5)	//������⵽����ϰ��Ϊ���������� 
		//if(0) //���迪�����ϣ���Ѵ��д���ע�ͣ�������һ�д���ȡ��ע�ͣ���֮
		{
			if(distr_ave==0&&distl_ave==20)
			{  
				//steer_control(0);
			   MOTOR_L_STOP
				 MOTOR_R_STOP
			}
			else
		{
			if(lenL<15||lenM<15||lenR<15)	//�����С��ͣ��
			{
				count1++;
				if(count1>=5)
				{MOTOR_L_STOP
				  MOTOR_R_STOP}
			}
			else 
			{
				count1=0; //����
					if(lenM<60)	//��⵽�ϰ��Ĭ������ת
				 {
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(29);
				 }
				 else if((lenL<lenR)&&lenL<45) //��ߴ����ϰ������ת
				{
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(29);
				}
				else if((lenL>lenR)&&lenR<45)	//�ұߴ����ϰ������ת
				{
					MOTOR_L_FORWARD
					MOTOR_R_FORWARD
					steer_control(-35);
				}
		  }
		}
		}
		else//uwbģʽ
		{
			MOTOR_L_FORWARD
			MOTOR_R_FORWARD
			
			if(distlr_ave<100) duoji=-deleta_origin*1; //�������ɽǶ�,����Խ����ƫתϵ��Խ��
			else if ((distl_ave>100)&&(distl_ave<200))  duoji=-deleta_origin*0.8; 
			else duoji=-deleta_origin*0.6; 
			
			if(duoji<0)duoji*=1.2;		//������У��,����ƫ��ʱ��̫����
			
			//����޷�
			if(duoji>29) duoji=29;		
			else if(duoji<-37) duoji=-37;
			if(distr_ave==0&&distl_ave==20)//��uwb����ʱ
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

