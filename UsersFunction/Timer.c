#include "Timer.h"
#include "stm32f10x.h"
#include "Filter.h"
#include "Mpu6050.h"

void 	Timer7_init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeInitStructure;
	
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	
  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;				//时钟分割
	TIM_TimeInitStructure.TIM_CounterMode=TIM_CounterMode_Up;				
	TIM_TimeInitStructure.TIM_Period=arr;					///自动重装的值
	TIM_TimeInitStructure.TIM_Prescaler=psc;			//不预分频  
	TIM_TimeBaseInit(TIM7,&TIM_TimeInitStructure);
	
	TIM_ITConfig(TIM7,TIM_IT_Update|TIM_IT_Trigger,ENABLE);
	
	TIM_Cmd(TIM7,ENABLE);
}




void TIM7_IRQHandler(void)                   
{
		Filter();
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);	
}




