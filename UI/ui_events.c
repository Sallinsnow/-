// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
#include "tim.h"
extern int FLAG1;
extern int FLAG2;
extern int FLAG3;
extern int FLAG4;
extern int FLAG5;

void WaveFormThree(lv_event_t * e)
{
	// Your code here 50hz,  10800 100 50
	if(FLAG3 == 1) FLAG3 = 0;
	else {
	FLAG3 = 1;
	__HAL_TIM_SET_PRESCALER(&htim13, 21600-1);
	}
}

void WaveFormTwo(lv_event_t * e)
{
	// Your code here 500hz 1080 100 50
	if(FLAG4 == 1) FLAG4 = 0;
	else{
	FLAG4 = 1;
	__HAL_TIM_SET_PRESCALER(&htim13, 2160-1);
	}
}

void WaveFormOne(lv_event_t * e)
{
	// Your code here 1khz 108 100 50
	if(FLAG5 == 1) FLAG5 = 0;
	else{
	FLAG5 = 1;
	__HAL_TIM_SET_PRESCALER(&htim13, 1080-1);
	}
}

void ChannelONE(lv_event_t * e)
{
	// Your code here CH1
}

void ChannelTWO(lv_event_t * e)
{
	// Your code here CH2
}

void TimeScaleFIVE(lv_event_t * e)
{
	// Your code here 100us
		__HAL_TIM_SET_PRESCALER(&htim2, 6-1); 
}

void TimeScaleFOUR(lv_event_t * e)
{
	// Your code here 500us
	__HAL_TIM_SET_PRESCALER(&htim2, 30-1);
}

void TimeScaleTHREE(lv_event_t * e)
{
	// Your code here 1ms
	__HAL_TIM_SET_PRESCALER(&htim2, 60-1);
	
}

void TimeScaleTWO(lv_event_t * e)
{
	// Your code here 5ms
	__HAL_TIM_SET_PRESCALER(&htim2, 300-1);
}

void TimeScaleONE(lv_event_t * e)
{
	// Your code here 10ms
	__HAL_TIM_SET_PRESCALER(&htim2, 600-1);
}

void StopWave(lv_event_t * e)
{
	// Your code here 
}

void ChannelOneVpp(lv_event_t * e)
{
	// Your code here CH1 Vpp
}

void ChannelTwoVpp(lv_event_t * e)
{
	// Your code here CH2 Vpp
}

void ChannelOneOn(lv_event_t * e)
{
	// Your code here
	FLAG1 = 1;
}

void ChannelOneOff(lv_event_t * e)
{
	// Your code here
	FLAG1 = 0;
}

void ChannelTwoOn(lv_event_t * e)
{
	// Your code here
	FLAG2 = 1;
}

void ChannelTwoOff(lv_event_t * e)
{
	// Your code here
	FLAG2 = 0;
}