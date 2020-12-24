#include "pid.h"


float PID_Position_float_2(float Angle , Pid_Structure *PID)
{
    PID->error = Angle - PID->desired;				//获取本次偏差
	PID->integ+= PID->error;									//获取积分
	PID->deriv = PID->error - PID->prevError;	//获取微分
	PID->prevError = PID->error;							//记录上次偏差
	
	if(PID->integLimit!=0)//integLimit为0时，积分不限幅
	{
		if(PID->integ >  PID->integLimit)  PID->integ =  PID->integLimit;//积分限幅
		if(PID->integ < -PID->integLimit)  PID->integ = -PID->integLimit;//积分限幅
	}
	
	PID->outP = PID->kp * PID->error;//计算比例部分的输出
	PID->outI = PID->ki * PID->integ;//计算积分部分的输出
	PID->outD = PID->kd * PID->deriv;//计算微分部分的输出
	
	if(PID->outPLimit!=0)//outPLimit为0时，P输出不限幅
	{
		if(PID->outP >=  PID->outPLimit) PID->outP =  PID->outPLimit;//P输出限幅
		if(PID->outP <= -PID->outPLimit) PID->outP = -PID->outPLimit;//P输出限幅
	}
	
	if(PID->outILimit!=0)//outILimit为0时，I输出不限幅
	{
		if(PID->outI >=  PID->outILimit) PID->outI =  PID->outILimit;//I输出限幅
		if(PID->outI <= -PID->outILimit) PID->outI = -PID->outILimit;//I输出限幅
	}
	
	if(PID->outDLimit!=0)//outDLimit为0时，D输出不限幅
	{
		if(PID->outD >=  PID->outDLimit) PID->outD =  PID->outDLimit;//D输出限幅
		if(PID->outD <= -PID->outDLimit) PID->outD = -PID->outDLimit;//D输出限幅
	}
	
	PID->output = PID->outP + PID->outI + PID->outD;//计算PID总输出
	
	if(PID->outputLimit!=0)//outputLimit为0时，总输出不限幅
	{
		if(PID->output >  PID->outputLimit) PID->output=  PID->outputLimit;//总输出限幅
		if(PID->output < -PID->outputLimit) PID->output= -PID->outputLimit;//总输出限幅
	}
	
	return PID->output;//返回总输出值
}

void PID_Init(Pid_Structure* pid)//初始化结构体各个变量
{
    //----------------------用户可修改的值------------------------------
	
	pid->desired   = 0; 			//目标值
	
	pid->kp 	   = 0.01;		    //比例增益
	pid->ki        = 0;				//积分增益
	pid->kd        = 0;				//微分增益
	
	pid->integLimit= 0; 			//积分限幅，若为0则不限幅
	pid->outPLimit = 0;				//P输出限幅，若为0则不限幅
	pid->outILimit = 0;				//I输出限幅，若为0则不限幅
	pid->outDLimit = 0;				//D输出限幅，若为0则不限幅
	pid->outputLimit = 0.5;		//总输出限幅，若为0则不限幅
	
	//----------------------用户可修改的值------------------------------
	
	//----------------------以下的值会在程序运行过程中自动修改，初始化时置0即可-------------------------------------
	pid->error     = 0; //这一次的差
	pid->prevError = 0;	//上一次的差
	pid->integ     = 0; //积分
	pid->deriv     = 0; //微分
	
	pid->outP      = 0; //P输出
	pid->outI      = 0; //I输出
	pid->outD      = 0; //D输出
	pid->output	   = 0; //总输出
}