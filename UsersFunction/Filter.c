#include "Filter.h"
#include "math.h"
#include "sys.h"


float Angle=0,Gyro_x=0;         //小车滤波后倾斜角度/角速度	
//******卡尔曼参数************
		
float  Q_angle=0.001;  
float  Q_gyro=0.003;
float  R_angle=0.5;
float  dt=0.005;	                  //dt为kalman滤波器采样时间;
char   C_0 = 1;
float  Q_bias=0, Angle_err=0;
float  PCt_0=0, PCt_1=0, E=0;
float  K_0=0, K_1=0, t_0=0, t_1=0;
float  Pdot[4] ={0,0,0,0};
float  PP[2][2] = { { 1, 0 },{ 0, 1 } };

//*********************************************************
// 卡尔曼滤波
//*********************************************************

//Kalman滤波，20MHz的处理时间约0.77ms；

void Kalman_Filter(float Gyro,float Accel)	
{
	Angle+=(Gyro - Q_bias) * dt;           //先验估计

	
	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分

	Pdot[1]= - PP[1][1];
	Pdot[2]= - PP[1][1];
	Pdot[3]=Q_gyro;
	
	PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
	PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err = Accel - Angle;
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 //后验估计误差协方差
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	Angle	+= K_0 * Angle_err;	 //后验估计
	Q_bias	+= K_1 * Angle_err;	 //后验估计
	Gyro_x   = Gyro - Q_bias;	 //输出值(后验估计)的微分=角速度
}
