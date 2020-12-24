#ifndef __ADD_H__
#define __ADD_H__
typedef struct
{
	float desired;		//< set point	>目标值
	float error;        //< error	>偏差
	float prevError;    //< previous error	>上一次偏差
	float integ;        //< integral	>偏差累加（积分）
	float integLimit;   //< integral limit. '0' means no limit.	>积分限幅，若为0则不限幅
	float deriv;        //< derivative	>本次偏差减去上一次偏差
	float kp;           //< proportional gain	>比例增益
	float ki;           //< integral gain	>积分增益
	float kd;           //< derivative gain	>微分增益
	float outP;         //< proportional output (debugging)	>P最终输出
	float outI;         //< integral output (debugging)	>I最终输出
	float outD;         //< derivative output (debugging) >D最终输出
	float outPLimit;		//< P output limit, absolute value. '0' means no limit.	>P限幅，若为0则不限幅
	float outILimit;		//< I output limit, absolute value. '0' means no limit.	>I限幅，若为0则不限幅
	float outDLimit;		//< D output limit, absolute value. '0' means no limit.	>D限幅，若为0则不限幅
	float outputLimit;  //< total PID output limit, absolute value. '0' means no limit.	>总输出限幅，若为0则不限幅
	float output;				//< total PID output >总输出
} Pid_Structure;

float PID_Position_float_2(float Angle , Pid_Structure *PID);

void PID_Init(Pid_Structure* pid);

#endif 
/* __ADD_H__ */



