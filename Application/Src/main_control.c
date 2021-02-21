#include "main_control.h"
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
#include "motor.h"

float x_distl=0;
float x_distr=0;

float distl_ave = 0.0;
float distr_ave = 0.0;

float deleta=0;
float deleta_origin=0;
float duoji=0;

void main_control_task(void *argument)
{
  /* USER CODE BEGIN main_control_task */
  /* Infinite loop */
  for(;;)
  {
		distl_ave = 0.5*(distl + last_distl);
		distr_ave = 0.5*(distr + last_distr);
		
    x_distl=sqrt((distl_ave*distl_ave-6400));
		x_distr=sqrt((distr_ave*distr_ave-6400));
		deleta=x_distr-x_distl;
		deleta_origin=distr_ave-distl_ave;
		
		last_distl = distl;
		last_distr = distr;
		duoji=-deleta*0.2;
		if(duoji>29)duoji=29;
		else if(duoji<-29)duoji=-29;
		steer_control(duoji);
		osDelay(10);
  }
  /* USER CODE END main_control_task */
}

